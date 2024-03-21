#include <SDL3_ttf/SDL_ttf.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <cmath>
#include <common/initializer/imgui.hpp>
#include <common/math.hpp>
#include <common/scale.hpp>
#include <common/sdl.hpp>
#include <editor/editor.hpp>
#include <level/file.hpp>

namespace Editor {
Editor::Editor()
  : mInitHandler(std::make_unique<Common::InitHandler>())
  , pWindow(nullptr)
  , pRenderer(nullptr)
  , mFont(nullptr)
  , mRun(true)
  , mMapLoaded(false)
  , mNewFile(false)
  , showNumbers(false)
  , showOverlay(false)
  , fileTiles(0)
  , tiles{}
  , mScale{}
  , mHideAllWindows(false)
  , mMouse(DEFAULT)
  , mActionManager(std::make_unique<Common::ActionManager>())
  , mOffset(0.0, 0.0) {}

Editor::~Editor() {
    mInitHandler->shutdown();

    if (mFont)
        TTF_CloseFont(mFont); // Clean the font

    fileTiles.Tiles.clear();
    visualOverlay.clear();

    TTF_Quit();
    SDL_Quit();
}

Common::ActionManager&
Editor::getActionManager() {
    return *mActionManager;
}

void
Editor::startup() {
    mInitHandler->addInitializer(std::make_shared<Common::SDLInitializer>(&pWindow, &pRenderer, "Editor"));
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

    mElements["TopMenu"]  = [this]() { uiMenu(); };
    mElements["Tiles"]    = [this]() { uiTiles(); };
    mElements["Grid"]     = [this]() { uiDrawGrid(); };
    mElements["Header"]   = [this]() { uiHeader(); };
    mElements["Assets"]   = [this]() { uiAssets(); };
    mElements["Mouse"]    = [this]() { uiMouse(); };
    mElements["Textures"] = [this]() { uiTexture(); };
    displayElement("TopMenu");
}

void
Editor::mainLoop() {
    SDL_Event event;

    while (mRun) {
            SDL_SetRenderDrawColor(pRenderer,
                                   fileHeader.Color.BackgroundRed,
                                   fileHeader.Color.BackgroundGreen,
                                   fileHeader.Color.BackgroundBlue,
                                   SDL_ALPHA_OPAQUE);
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        mFPSTimer.start();

        SDL_RenderClear(pRenderer);
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
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
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(pRenderer);
}

[[maybe_unused]] std::list<std::function<bool(SDL_Event*)>>&
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
Editor::click(const float& x, const float& y) {
    if (fileTiles.Size != 0 && !clickOnUi(x, y)) {
        auto index =
          Common::getIndex(Common::getClickCoords(x + (mOffset.X / -1.0f), y + (mOffset.Y / -1.0f), mScale), fileHeader.Level.SizeX);
        if (index.has_value()) {
            const auto pos = index.value();

            switch (mMouse) {
                case TEXTURE: {
                    // Add tile to the list
                    mLevelCoords.emplace(Common::getClickCoords(x + (mOffset.X / -1.0f), y + (mOffset.Y / -1.0f), mScale));
                    // Fetching the texture
                    auto simpleTexture = GET_SIMPLE(mSelectedTexture);
                    // Add texture to tile
                    tiles[pos].addData(simpleTexture.Texture, simpleTexture[-1].second);
                    // Stuff that shall be added to the files
                    fileTiles.Tiles[pos].Type |= Level::File::TEXTURE;
                    //Increment visual overlay
                    visualOverlay[pos].incrementCounter();
                    // Search if the asset have been used before
                    const auto id = Level::File::findAsset(mSelectedTexture, fileAssets);
                    if (id.has_value())
                        fileTiles.Tiles[pos].Id.emplace_back(id.has_value());
                    else
                        fileTiles.Tiles[pos].Id.emplace_back(Level::File::addAsset(mSelectedTexture, fileAssets));
                } break;
                case REMOVE:
                    tiles[pos].clear(); //Clear the vector

                    fileTiles.Tiles[pos].Type = Level::File::BLANK;
                    fileTiles.Tiles[pos].Id.clear();

                    visualOverlay[pos].resetCounter();
                    {
                        //We need to remove the coord from the list of used coordinates.
                        auto it = mLevelCoords.find(Common::getClickCoords(x, y, mScale));
                        if(it != mLevelCoords.end())
                            mLevelCoords.erase(it);
                    }
                    break;

                case WALL:
                    fileTiles.Tiles[pos].Type |= Level::File::WALL;
                    visualOverlay[pos].newOverlay(GET_SDL("87ED17"));
                    break;
                case OBSTACLE:
                    fileTiles.Tiles[pos].Type |= Level::File::OBSTACLE;
                    visualOverlay[pos].newOverlay(GET_SDL("1D35FA"));
                    break;
                case DEFAULT:
                default:
                    break;
            }
        }
    }
}


}