#pragma once
#include <SDL3/SDL.h>
#include <common/include.hpp>
#include <memory>
#include <list>
#include <utility/timer.hpp>

namespace Editor {
class Editor {
  public:
    Editor();
    ~Editor();

    void startup(); // Load all functions related to startup
    void mainLoop();

    Common::ActionManager& getActionManager();

    void addEventWatcher(std::function<bool(SDL_Event*)> handler);                    // Add event to listen
    void queueEventHandler(Uint32 evenType, std::function<bool(SDL_Event*)> handler); // Add event in queue
    void queueProcessHandler(std::function<void(int)> handler);


  protected:
  private:
    std::unique_ptr<Common::InitHandler> mInitHandler;
    // Events
    std::unique_ptr<Common::ActionManager>             mActionManager;
    std::list<std::function<bool(SDL_Event*)>> mEventWatcher; // List of all event to watch for
    std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>> mEvents;
    std::list<std::tuple<std::function<void(int)>, Utility::Timer>>                 mProcessing;

    SDL_Window*   pWindow;
    SDL_Renderer* pRenderer;
};
}