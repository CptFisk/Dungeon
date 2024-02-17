#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <common/include.hpp>
#include <list>
#include <memory>
#include <utility/timer.hpp>
#include <level/structures.hpp>

namespace Editor {
class Editor {
  public:
    Editor();
    ~Editor();

    void startup(); // Load all functions related to startup
    void mainLoop();

    Common::ActionManager& getActionManager();

    std::list<std::function<bool(SDL_Event*)>>&                             getEventList(); // Get the list of events
    std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>>& getEvents();    // Get the list of events
    std::list<std::tuple<std::function<void(int)>, Utility::Timer>>&        getProcessing();

    void terminate();

  protected:
    void uiMenu();
    void present();

  private:
    bool mRun;
    bool mMapLoaded;
    std::unique_ptr<Common::InitHandler> mInitHandler;
    // Events
    std::unique_ptr<Common::ActionManager>     mActionManager;
    std::list<std::function<bool(SDL_Event*)>> mEventWatcher; // List of all event to watch for
    std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>> mEvents;
    std::list<std::tuple<std::function<void(int)>, Utility::Timer>>        mProcessing;

    Utility::Timer mFPSTimer; // To lock fps

    SDL_Window*   pWindow;
    SDL_Renderer* pRenderer;
    TTF_Font*     mFont;

    Level::LevelHeader mLevelHeader;
};
}