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

    std::list<std::function<bool(SDL_Event*)>>& getEventList(); // Get the list of events
    std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>>& getEvents();    //Get the list of events
    std::list<std::tuple<std::function<void(int)>, Utility::Timer>>& getProcessing();


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