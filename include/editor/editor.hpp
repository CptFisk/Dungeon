#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <common/include.hpp>
#include <graphics/graphics.hpp>
#include <level/structures.hpp>
#include <list>
#include <memory>
#include <utility/timer.hpp>

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
    void uiProjectHeader();
    void uiDrawGrid();
    void present();

  private:
    Common::Scale mScale;

    bool                                 mRun;
    bool                                 mMapLoaded;
    bool                                 mNewFile; // Start of a new project
    std::unique_ptr<Common::InitHandler> mInitHandler;
    std::shared_ptr<Graphics::Graphics>  mGraphics;

    // Events
    std::unique_ptr<Common::ActionManager>     mActionManager;
    std::list<std::function<bool(SDL_Event*)>> mEventWatcher; // List of all event to watch for
    std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>> mEvents;
    std::list<std::tuple<std::function<void(int)>, Utility::Timer>>        mProcessing;

    Utility::Timer mFPSTimer; // To lock fps

    SDL_Window*   pWindow;
    SDL_Renderer* pRenderer;
    TTF_Font*     mFont;
    SDL_Color     mWhite = { 255, 255, 255 }; // White color

    // Bits
    bool mShowProjectHeader;
    bool mShowGrid;

    Level::LevelHeader mLevelHeader;
};
}