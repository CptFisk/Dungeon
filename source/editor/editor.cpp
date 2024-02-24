#include <SDL3_ttf/SDL_ttf.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <cmath>
#include <common/initializer/imgui.hpp>
#include <common/math.hpp>
#include <common/scale.hpp>
#include <common/sdl.hpp>
#include <editor/editor.hpp>
#include <level/structures.hpp>

namespace Editor {
Editor::Editor()
  : mInitHandler(std::make_unique<Common::InitHandler>())
  , pWindow(nullptr)
  , pRenderer(nullptr)
  , mFont(nullptr)
  , mRun(true)
  , mMapLoaded(false)
  , mNewFile(false)
  , pLevelHeader(nullptr)
  , pAssets(nullptr)
  , pTile(nullptr)
  , pVisualTile(nullptr)
  , mScale{}
  , mHideAllWindows(false)
  , mMouse(DEFAULT)
  , mActionManager(std::make_unique<Common::ActionManager>()) {}

Editor::~Editor() {
    mInitHandler->shutdown();

    const int size = pLevelHeader != nullptr ? pLevelHeader->Level.SizeX * pLevelHeader->Level.SizeY : 0;
    if (mFont)
        TTF_CloseFont(mFont); // Clean the font
    // Clean stuff that we need to know the size for
    Level::deleteTile(pTile, size);
    for (int i = 0; i < size; i++) {
        delete pVisualTile[i];
        delete pVisualTile[i];
    }
    delete[] pVisualTile;
    delete[] pVisualTileType;


    delete pLevelHeader;
    delete pAssets;

    TTF_Quit();
    SDL_Quit();
}

Common::ActionManager&
Editor::getActionManager() {
    return *mActionManager;
}

void
Editor::startup() {
    mInitHandler->addInitializer(std::make_shared<Common::SDLInitializer>(&pWindow, &pRenderer));
    mInitHandler->addInitializer(std::make_shared<Common::ImGuiInitializer>(&pWindow, &pRenderer));
    mInitHandler->startup();

    Common::calculateGameScale(mScale, pWindow);
    // Generate graphics
    mGraphics = std::make_shared<Graphics::Graphics>(pRenderer, mScale);
    mGraphics->init();

    // Try to load the font
    mFont = TTF_OpenFont("rsrc/fonts/Arial.ttf", 14);

    // Generating textures
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 12; y++) {
            const std::string name    = std::to_string(x) + "," + std::to_string(y);
            auto              surface = TTF_RenderText_Solid(mFont, name.c_str(), mWhite);
            mGraphics->addTexture(name, SDL_CreateTextureFromSurface(pRenderer, surface));
            SDL_DestroySurface(surface); // Cleaning
        }
    }

    Common::addEventWatcher([&](SDL_Event* evt) { return mActionManager->eventHandler(evt); }, mEventWatcher);

    mElements["Top"]    = [this]() { uiMenu(); };
    mElements["Tiles"]  = [this]() { uiTiles(); };
    mElements["Grid"]   = [this]() { uiDrawGrid(); };
    mElements["Header"] = [this]() { uiHeader(); };
    mElements["Assets"] = [this]() { uiAssets(); };
    mElements["Mouse"]  = [this]() { uiMouse(); };
    displayElement("Top");
}

void
Editor::mainLoop() {
    SDL_Event event;

    while (mRun) {
        if (pLevelHeader)
            SDL_SetRenderDrawColor(pRenderer,
                                   pLevelHeader->Color.BackgroundRed,
                                   pLevelHeader->Color.BackgroundGreen,
                                   pLevelHeader->Color.BackgroundBlue,
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
        present();

        auto ticks = mFPSTimer.getTicks();
        if (ticks < 1000.0 / 60)
            SDL_Delay((1000.0 / 60) - ticks);
    }
}

void
Editor::present() {
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
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
Editor::click(const float& x, const float& y) {
    if (pTile != nullptr && !clickOnUi(x, y)) {
        auto ix = static_cast<int>(x);
        auto iy = static_cast<int>(y);

        auto index = Common::getIndex(Common::getClickCoords(x, y, mScale), pLevelHeader);
        switch (mMouse) {
            case TEXTURE:
                if (pTile[index]->Type == Level::BLANK) {
                    auto simpleTexture           = mGraphics->getBaseTexture("PurpleFloor");
                    pVisualTile[index]->Texture  = simpleTexture.Texture;
                    pVisualTile[index]->Viewport = simpleTexture[-1].second;

                    pTile[index]->Type |= Level::BACKGROUND;
                    pTile[index]->Id = 1;
                    mLevelCoords.emplace(ix, iy);
                } else if (pTile[index]->Type == Level::BACKGROUND) {
                    pVisualTile[index]->Texture = mGraphics->getTexture("PurpleFloor");
                }
                break;
            case REMOVE:
                if (pTile[index]->Type == Level::BACKGROUND) {
                    pVisualTile[index]->Texture = nullptr;
                    pTile[index]->Type          = Level::BLANK;
                    pTile[index]->Id            = 0;

                    auto it = mLevelCoords.find(std::make_pair(ix, iy));
                    if (it != mLevelCoords.end())
                        mLevelCoords.erase(it);
                }
                break;
            default:
            case DEFAULT:
                break;
        }
    }
}

Editor::typeVisualTile**
Editor::newVisualTile() {
    // Allocate data
    const int sizeX = pLevelHeader->Level.SizeX;
    const int sizeY = pLevelHeader->Level.SizeY;
    const int size  = pLevelHeader->Level.SizeX * pLevelHeader->Level.SizeY;

    auto data = new Editor::typeVisualTile* [size] {};
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            auto index  = Common::getIndex(x, y, pLevelHeader);
            data[index] = new Editor::typeVisualTile(Common::newSDL_FRect(x, y, mScale));
        }
    }
    return data;
}

Editor::typeVisualTileType**
Editor::newVisualTileType() {
    const int sizeX = pLevelHeader->Level.SizeX;
    const int sizeY = pLevelHeader->Level.SizeY;
    const int size  = pLevelHeader->Level.SizeX * pLevelHeader->Level.SizeY;

    auto data = new Editor::typeVisualTileType* [size] {};
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            auto index  = Common::getIndex(x, y, pLevelHeader);
            data[index] = new Editor::typeVisualTileType(nullptr, Common::newSDL_FRect(x, y, mScale));
        }
    }
    return data;
}


}