#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <common/initializer/imgui.hpp>
#include <common/interrupt.hpp>
#include <common/math.hpp>
#include <common/scale.hpp>
#include <editor/editor.hpp>
#include <level/file.hpp>

namespace Editor {
Editor::Editor(const int& w, const int& h)
  : mInitHandler(std::make_unique<Common::InitHandler>())
  , requestDimensionW(w)
  , requestDimensionH(h)
  , pWindow(nullptr)
  , pRenderer(nullptr)
  , mRun(true)
  , mMapLoaded(false)
  , mNewFile(false)
  , showNumbers(false)
  , showOverlay(false)
  , showGrid(false)
  , fileTiles(0)
  , editorTiles{}
  , mScale{}
  , mHideAllWindows(false)
  , mMouse(Mouse::DEFAULT)
  , mActionManager(std::make_unique<Common::ActionManager>())
  , mOffset(0.0, 0.0)
  , mPlayerSpawn{} {}

Editor::~Editor() {
    // De-spawn all threads
    for (auto& thread : mThreads) {
        thread.join();
    }

    mGraphics.reset();
    mInitHandler->shutdown();

    fileTiles.Tiles.clear();
    visualOverlay.clear();

    SDL_Quit();
}

Common::ActionManager&
Editor::getActionManager() {
    return *mActionManager;
}

void
Editor::startup() {
    mThreads.push_back(spawnInterrupt(10));

    mInitHandler->addInitializer(
      std::make_shared<Common::SDLInitializer>(pWindow, pRenderer, requestDimensionW, requestDimensionH, "Editor"));
    mInitHandler->addInitializer(std::make_shared<Common::ImGuiInitializer>(&pWindow, &pRenderer));
    mInitHandler->startup();

    Common::calculateGameScale(mScale, pWindow);

    // Setup perspective
    mPerspective = std::make_unique<Common::Perspective>(pRenderer, mOffset.X, mOffset.Y);
    // Generate graphics
    mGraphics = std::make_shared<Graphics::Graphics>(pRenderer);
    mGraphics->init();

    mTextures = mGraphics->getAllTextureNames();
    if (!mTextures.empty()) {
        std::sort(mTextures.begin(), mTextures.end());
        mSelectedTexture = mTextures[0];
    }

    Common::addEventWatcher([&](SDL_Event* evt) { return mActionManager->eventHandler(evt); }, mEventWatcher);
    // Update all graphics
    mInterrupts[10]->addFunction([&]() { mGraphics->updateAnimatedTexture(); });

    mElements["TopMenu"]    = [this]() { uiMenu(); };
    mElements["Tiles"]      = [this]() { uiTiles(); };
    mElements["Header"]     = [this]() { uiHeader(); };
    mElements["Assets"]     = [this]() { uiAssets(); };
    mElements["Mouse"]      = [this]() { uiMouse(); };
    mElements["Textures"]   = [this]() { uiTexture(); };
    mElements["DoorsPopup"] = [this]() { uiDoorPopup(); };
    mElements["Doors"]      = [this]() { uiDoors(); };
    displayElement("TopMenu");
}

void
Editor::mainLoop() {
    SDL_Event event;
    while (mRun) {
        SDL_SetRenderDrawColor(
          pRenderer, fileHeader.Color.BackgroundRed, fileHeader.Color.BackgroundGreen, fileHeader.Color.BackgroundBlue, SDL_ALPHA_OPAQUE);
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        mFPSTimer.start();

        SDL_RenderClear(pRenderer);

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            bool accepted = true;

            for (auto& handler : mEventWatcher) {
                if (!handler(&event)) {
                    accepted = false;
                    break;
                }
            }

            if (accepted && mEvents.find(event.type) != mEvents.end()) {
                auto handlers = mEvents[event.type];
                for (auto& handler : handlers) {
                    if (!handler(&event))
                        break;
                }
            }
        }

        for (auto& [handler, timer] : mProcessing) {
            handler(timer.getTicks());
            timer.start();
        }

        // Draw all visible elements
        for (const auto& element : mVisibleElements)
            element();
        if (mHideAllWindows) {
            mVisibleElements.clear();
            mWindows.clear();
            mHideAllWindows = false;
            for (auto& [name, flag] : mWindowOpen)
                flag = false;
        } else {
            for (const auto& element : mElementsToHide) {
                auto it = mElements.find(element);
                if (it != mElements.end())
                    mVisibleElements.erase(it->second);
                if (mWindows.find(element) != mWindows.end())
                    mWindows.erase(it->first);
            }
            mElementsToHide.clear();
            for (auto& [name, flag] : mWindowOpen) {
                if (!flag)
                    mVisibleElements.erase(mElements.find(name)->second);
            }
        }

        // Adding new items that should be visible next scan
        for (const auto& element : mElementsToShow) {
            auto it = mElements.find(element);
            if (mElements.find(element) != mElements.end())
                mVisibleElements.insert(it->second);
            mWindowOpen[element] = true;
        }
        mElementsToShow.clear();
        uiTiles();

        for (auto& [texture, position] : mEdges) {
            mPerspective->render(texture, nullptr, &position);
        }
        uiDrawGrid();
        // ImGui::ShowDemoWindow();
        present();

        auto ticks = mFPSTimer.getTicks();
        if (ticks < 1000.0 / 60)
            SDL_Delay((1000.0 / 60) - ticks);
    }
}

void
Editor::move(Directions direction) {
    mPerspective->move(direction, 5.0);
}

void
Editor::present() {
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(pRenderer);
}

std::list<std::function<bool(SDL_Event*)>>&
Editor::getEventList() {
    return mEventWatcher;
}

std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>>&
Editor::getEvents() {
    return mEvents;
}

std::list<std::tuple<std::function<void(int)>, Utility::Timer>>&
Editor::getProcessing() {
    return mProcessing;
}

void
Editor::terminate() {
    mRun = false;
}

void
Editor::click() {
    const auto x = mActionManager->mouseX;
    const auto y = mActionManager->mouseY;
    if (fileTiles.Size != 0 && !clickOnUi(x, y)) {
        const auto clickCoord = Common::getClickCoords(x + (mOffset.X / -1.0f), y + (mOffset.Y / -1.0f), mScale);
        clickedCoord = clickCoord;    //To display coords
        auto       index      = Common::getIndex(clickCoord, fileHeader.Level.SizeX);
        if (index.has_value()) {
            const auto pos = index.value();

            switch (mMouse) {
                case Mouse::TEXTURE: {
                    // Add tile to the list
                    mLevelCoords.emplace(Common::getClickCoords(x + (mOffset.X / -1.0f), y + (mOffset.Y / -1.0f), mScale));

                    SDL_Texture* texture  = {};
                    SDL_Rect*    viewport = {};
                    int          w;
                    int          h;
                    if (mSelectedTexture.first == Graphics::TextureTypes::SIMPLE_TEXTURE) {
                        auto& simpleTexture = GET_SIMPLE(mSelectedTexture.second);
                        w                   = simpleTexture.Width;
                        h                   = simpleTexture.Height;
                        texture             = simpleTexture.getTexture();
                        viewport            = &simpleTexture.getRandomView();
                        fileTiles.Tiles[pos].Type |= static_cast<uint8_t>(Level::File::TileType::TEXTURE);
                    } else {
                        auto& animatedTexture = GET_ANIMATED(mSelectedTexture.second);
                        w                     = animatedTexture->Width;
                        h                     = animatedTexture->Height;
                        texture               = animatedTexture->getTexture();
                        viewport              = animatedTexture->getViewport();

                        // Check if this value is higher than previous
                        animationValues[mSelectedTexture.second] = static_cast<int>(animatedTexture->getViewports().size() * animatedTexture->getTicks());

                        fileTiles.Tiles[pos].Type |= static_cast<uint8_t>(Level::File::TileType::ANIMATED_TEXTURE);
                    }
                    // Add texture to tile
                    editorTiles[pos].addData(texture, viewport, w, h, mScale);
                    // Increment visual overlay
                    visualOverlay[pos].incrementCounter();
                    // Search if the asset have been used before
                    const auto id = Level::File::findAsset(mSelectedTexture.second, fileAssets);
                    if (id.has_value())
                        fileTiles.Tiles[pos].Id.emplace_back(id.value());
                    else
                        fileTiles.Tiles[pos].Id.emplace_back(Level::File::addAsset(mSelectedTexture.second, fileAssets));

                } break;
                case Mouse::REMOVE:
                    editorTiles[pos].clear(); // Clear the vector

                    fileTiles.Tiles[pos].Type = static_cast<uint8_t>(Level::File::TileType::BLANK);
                    fileTiles.Tiles[pos].Id.clear();

                    visualOverlay[pos].resetCounter();
                    {
                        // We need to remove the coord from the list of used coordinates.
                        auto it = mLevelCoords.find(Common::getClickCoords(x, y, mScale));
                        if (it != mLevelCoords.end())
                            mLevelCoords.erase(it);
                    }
                    break;

                case Mouse::WALL:
                    fileTiles.Tiles[pos].Type |= static_cast<uint8_t>(Level::File::TileType::WALL);
                    visualOverlay[pos].newOverlay(GET_SDL("87ED17"));
                    break;
                case Mouse::OBSTACLE:

                    fileTiles.Tiles[pos].Type |= static_cast<uint8_t>(Level::File::TileType::OBSTACLE);
                    visualOverlay[pos].newOverlay(GET_SDL("1D35FA"));
                    break;
                case Mouse::PLAYER_SPAWN: {
                    auto coords              = Common::getClickCoords(x + (mOffset.X / -1.0f), y + (mOffset.Y / -1.0f), mScale);
                    mPlayerSpawn.x           = static_cast<float>(coords.first) * 16.0f * mScale.factorX;
                    mPlayerSpawn.y           = static_cast<float>(coords.second) * 16.0f * mScale.factorY;
                    mPlayerSpawn.w           = 16.0f * mScale.factorX;
                    mPlayerSpawn.h           = 16.0f * mScale.factorY;
                    fileHeader.Level.PlayerX = coords.first;
                    fileHeader.Level.PlayerY = coords.second;
                } break;
                case Mouse::DOORS:
                    doorsPopup.x = x;
                    doorsPopup.y = y;
                    displayElement("DoorsPopup");

                case Mouse::DEFAULT:
                default:
                    break;
            }
        }
    }
}

std::thread
Editor::spawnInterrupt(const long& time) {
    auto thread = std::thread([&]() {
        auto interrupt    = std::make_shared<Common::Interrupt>(time, mRun);
        mInterrupts[time] = interrupt;
        interrupt->execute();
    });
    return thread;
}

}