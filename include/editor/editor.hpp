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
    Editor();  // Constructor
    ~Editor(); // De-constructor

    void startup();  // Load all functions related to startup
    void mainLoop(); // Were all the magic happen

    Common::ActionManager& getActionManager(); // Used when binding clicks, events

    std::list<std::function<bool(SDL_Event*)>>&                             getEventList(); // Get the list of events
    std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>>& getEvents();    // Get the list of events
    std::list<std::tuple<std::function<void(int)>, Utility::Timer>>&        getProcessing();

    void terminate();                           // Kill the editor
    void click(const float& x, const float& y); // Click
  protected:
    void uiMenu();     // Top menu
    void uiHeader();   // Display current open project settings
    void uiDrawGrid(); // Draw a basic grid over the area
    void uiAssets();   // Display the metadata related to the map
    void present();    // Render all graphic

    // Select an index in map
    int getIndex(const float& x, const float& y);
    int getIndex(const std::pair<int,int> &coords);
    int getIndex(const int& x, const int& y);


    std::pair<SDL_Texture*, SDL_FRect>** newVisualTile();
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
    bool mShowHeader;
    bool mShowGrid;
    bool mShowAssets;
    bool mShowToolbox;

    // Map data
    Level::Header*                       pLevelHeader;
    Level::Assets*                       pAssets;
    Level::Tile**                        pTile;
    std::pair<SDL_Texture*, SDL_FRect>** pVisualTile; // Used for drawing stuff
};
}