#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <common/include.hpp>
#include <editor/structures.hpp>
#include <graphics/graphics.hpp>
#include <graphics/structures.hpp>
#include <level/structures.hpp>
#include <list>
#include <memory>
#include <set>
#include <utility/timer.hpp>

namespace Editor {
class Editor {
  public:
    Editor();  // Constructor
    ~Editor(); // De-constructor

    void startup();  // Load all functions related to startup
    void mainLoop(); // Were all the magic happen

    Common::ActionManager& getActionManager(); // Used when binding clicks, events

    [[maybe_unused]] std::list<std::function<bool(SDL_Event*)>>& getEventList(); // Get the list of events
    [[maybe_unused]] std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>>&
    getEvents(); // Get the list of events
    [[maybe_unused]] std::list<std::tuple<std::function<void(int)>, Utility::Timer>>& getProcessing();

    void terminate();                           // Kill the editor
    void click(const float& x, const float& y); // Click
  protected:
    [[maybe_unused]] void        displayElement(const std::string& element);
    [[maybe_unused]] void        hideElement(const std::string& element);
    [[maybe_unused]] void        hideAllElements();
    [[maybe_unused]] bool        isElementVisible(const std::string& element);
    [[maybe_unused]] bool        clickOnUi(const float& x, const float& y);
    [[maybe_unused]] static bool isOverlap(const float& value, const float& low, const float& high);

    void uiMenu();     // Top menu
    void uiHeader();   // Display current open project settings
    void uiDrawGrid(); // Draw a basic grid over the area
    void uiAssets();   // Display the metadata related to the map
    void uiMouse();
    void uiTiles();
    void present(); // Render all graphic

  private:
    Common::typeScale mScale;

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
    Mouse         mMouse;

    // Windows
    struct typeWindowCovering {
        ImVec2 Position;
        ImVec2 Size;
    };
    struct typeElementsCompare {
        bool operator()(const std::function<void()>& lhs, const std::function<void()>& rhs) const {
            return lhs.target_type().hash_code() < rhs.target_type().hash_code();
        }
    };
    std::unordered_map<std::string, typeWindowCovering>    mWindows; // Contains the position and sizes of all windows
    std::unordered_map<std::string, bool>                  mWindowOpen; // True if a window is open
    std::vector<std::string>                               mElementsToHide;
    std::vector<std::string>                               mElementsToShow;
    std::unordered_map<std::string, std::function<void()>> mElements; // Contain all graphical elements
    std::set<std::function<void()>, typeElementsCompare>   mVisibleElements;
    bool                                                   mHideAllWindows; // True if all elements should be hidden

    // Map data
    Level::typeHeader*    pLevelHeader;
    Level::typeAssets*    pAssets;
    Level::typeTileData** pTile;
    struct typeVisualTile {
        SDL_Texture* Texture;
        SDL_FRect    Position;
        SDL_FRect    Viewport;
        explicit typeVisualTile(const SDL_FRect& position)
          : Texture(nullptr)
          , Viewport(SDL_FRect{ 0.0f, 0.0f, 0.0f, 0.0f })
          , Position(position) {}
    }** pVisualTile;

    struct typeVisualTileType {
        SDL_Texture* Texture;
        SDL_FRect    Position;
        typeVisualTileType(SDL_Texture* texture, const SDL_FRect position)
          : Texture(texture)
          , Position(position) {}
    }** pVisualTileType;

    typeVisualTile**     newVisualTile();
    typeVisualTileType** newVisualTileType();

    struct comparePair {
        bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
            return (lhs.first + lhs.second) < (rhs.first + rhs.second);
        }
    };
    std::set<std::pair<int, int>, comparePair> mLevelCoords; // A list of coordinates that is used
};
}