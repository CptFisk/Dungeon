#include <SDL3_ttf/SDL_ttf.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <cmath>
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
  , mShowHeader(false)
  , mShowAssets(false)
  , mShowToolbox(false)
  , mShowGrid(true)
  , mNewFile(false)
  , pLevelHeader(nullptr)
  , pAssets(nullptr)
  , pTile(nullptr)
  , pVisualTile(nullptr)
  , mScale{}
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
    }
    delete[] pVisualTile;

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
        uiTiles();
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
    if (pTile != nullptr) {
        auto index                = getIndex(getClickCoords(x, y));
        pVisualTile[index]->first = mGraphics->getTexture("PurpleFloor");
        pTile[index]->Type        = Level::BACKGROUND;
        pTile[index]->Id          = 1;
        pLevelHeader->Level.Types[Level::BACKGROUND]++;
    }
}

std::pair<SDL_Texture*, SDL_FRect>**
Editor::newVisualTile() {
    // Allocate data
    const int sizeX = pLevelHeader->Level.SizeX;
    const int sizeY = pLevelHeader->Level.SizeY;
    const int size  = pLevelHeader->Level.SizeX * pLevelHeader->Level.SizeY;

    auto data = new std::pair<SDL_Texture*, SDL_FRect>* [size] {};
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            // Start to generate
            auto xf    = static_cast<float>(x);
            auto yf    = static_cast<float>(y);
            auto index = getIndex(x, y);

            data[index] = new std::pair<SDL_Texture*, SDL_FRect>(
              nullptr,
              SDL_FRect{
                xf * 16.0f * mScale.ScaleX, yf * 16.0f * mScale.ScaleY, 16.0f * mScale.ScaleX, 16.0f * mScale.ScaleY });
        }
    }
    return data;
}

int
Editor::getIndex(const float& x, const float& y) {
    return getIndex(static_cast<int>(x), static_cast<int>(y));
}

int
Editor::getIndex(const std::pair<int, int>& coords) {
    return getIndex(coords.first, coords.second);
}

int
Editor::getIndex(const int& x, const int& y) {
    if (pLevelHeader == nullptr)
        return size_t();
    auto _x     = static_cast<int>(x);
    auto _y     = static_cast<int>(y);
    auto _width = static_cast<int>(pLevelHeader->Level.SizeX);

    return _x + _y * _width;
}

std::pair<int, int>
Editor::getClickCoords(const float& x, const float& y) {

    auto _x = std::floor(static_cast<float>(x) / (16.0f * mScale.ScaleX));
    auto _y = std::floor(static_cast<float>(y) / (16.0f * mScale.ScaleY));
    return std::make_pair(_x, _y);
}
}