#include <SDL3_ttf/SDL_ttf.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <common/imgui.hpp>
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
  , mShowProjectHeader(false)
  , mShowMapMeta(false)
  , mShowToolbox(false)
  , mShowGrid(true)
  , mNewFile(false)
  , pLevelHeader(nullptr)
  , pAssets(nullptr)
  , pTile(nullptr)
  , mScale{}
  , mActionManager(std::make_unique<Common::ActionManager>()) {}

Editor::~Editor() {
    mInitHandler->shutdown();

    if (mFont)
        TTF_CloseFont(mFont); // Clean the font
    delete pLevelHeader;
    delete pAssets;
    delete pTile;

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
}

void
Editor::mainLoop() {
    SDL_Event event;

    while (mRun) {
        if (pLevelHeader)
            SDL_SetRenderDrawColor(pRenderer,
                                   pLevelHeader->BackgroundRed,
                                   pLevelHeader->BackgroundGreen,
                                   pLevelHeader->BackgroundBlue,
                                   SDL_ALPHA_OPAQUE);
        ImGui::NewFrame();
        mFPSTimer.start();

        ImGui::ShowDemoWindow();

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

        // SDL_RenderTexture(pRenderer, texture, NULL, &dstRect);
        uiDrawGrid();
        uiMenu();
        uiAssets();
        uiHeader();

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
    if(pTile != nullptr){
        pTile[getIndex(x, y)]->Id = 1;
        pTile[getIndex(x,y)]->Type = Level::Background;
    }
}

int
Editor::getIndex(const float& x, const float& y) {
    if (pLevelHeader == nullptr)
        return size_t();

    return static_cast<int>(floor((x / (16.0 * mScale.ScaleX)))) +
           static_cast<int>(floor(y / (16.0 * mScale.ScaleY)) * pLevelHeader->MapSizeX);
}

}