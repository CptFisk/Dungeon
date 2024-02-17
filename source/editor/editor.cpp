#include <common/imgui.hpp>
#include <common/sdl.hpp>
#include <editor/editor.hpp>

namespace Editor {
Editor::Editor()
  : mInitHandler(std::make_unique<Common::InitHandler>())
  , pWindow(nullptr)
  , pRenderer(nullptr)
  , mRun(true),
   mActionManager(std::make_unique<Common::ActionManager>()){}

Editor::~Editor() {
    mInitHandler->shutdown();
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


    Common::addEventWatcher([&](SDL_Event* evt) { return mActionManager->eventHandler(evt); }, mEventWatcher);
}

void
Editor::mainLoop() {
    SDL_Event event;
    while (mRun) {
        mFPSTimer.start();

        SDL_RenderClear(pRenderer);
        while (SDL_PollEvent(&event)) {
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

        present();

        auto ticks = mFPSTimer.getTicks();
        if (ticks < 1000.0 / 60)
            SDL_Delay((1000.0 / 60) - ticks);
    }
}

void
Editor::present() {
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

}