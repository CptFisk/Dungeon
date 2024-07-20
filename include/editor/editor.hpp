#pragma once
#include <SDL.h>
#include <common/include.hpp>
#include <common/perspective.hpp>
#include <editor/tile.hpp>
#include <editor/utility/mouse.hpp>
#include <editor/utility/mouseLightning.hpp>
#include <editor/visualTile.hpp>
#include <global.hpp>
#include <graphics/graphics.hpp>
#include <graphics/structures.hpp>
#include <level/file.hpp>
#include <list>
#include <memory>
#include <set>
#include <thread>
#include <unordered_map>
#include <utility/timer.hpp>

namespace Editor {
class Editor {
  public:
    Editor(const int& w, const int& h); // Constructor
    ~Editor();                          // De-constructor

    void                   startup();  // Load all functions related to startup
    void                   mainLoop(); // Were all the magic happen
    void                   move(Directions direction);
    Common::ActionManager& getActionManager(); // Used when binding clicks, events

    [[maybe_unused]] std::list<std::function<bool(SDL_Event*)>>&                             getEventList(); // Get the list of events
    [[maybe_unused]] std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>>& getEvents();    // Get the list of events
    [[maybe_unused]] std::list<std::tuple<std::function<void(int)>, Utility::Timer>>&        getProcessing();

    void terminate(); // Kill the editor
    void click();     // Click
  protected:
    std::thread spawnInterrupt(const long& time); // Spawn a thread

    void loadLevel(const Level::File::typeLevelData& data);
    void removeSpecificTexture(const std::string& name, std::vector<Tile*>& tiles, const uint8_t& id);

    [[maybe_unused]] void        displayElement(const std::string& element);
    [[maybe_unused]] void        hideElement(const std::string& element);
    [[maybe_unused]] void        hideAllElements();
    [[maybe_unused]] bool        isElementVisible(const std::string& element);
    [[maybe_unused]] bool        clickOnUi(const int& x, const int& y, const std::string& element);
    [[maybe_unused]] bool        clickOnUi(const int& x, const int& y);
    [[maybe_unused]] static bool isOverlap(const float& value, const float& low, const float& high);

    // Windows
    struct typeWindowCovering {
        ImVec2 Position;
        ImVec2 Size;
    };

    void uiMenu();                                                                            // Top menu
    void uiHeader(typeWindowCovering& area, bool& open, Level::File::typeHeaderData& header); // Display current open project settings
    void uiDrawGrid();                                                                        // Draw a basic grid over the area
    void uiAssets(typeWindowCovering& area, bool& open, Level::File::typeAssets& assets);     // Display the metadata related to the map
    void uiMouse(typeWindowCovering& area, bool& open, Mouse& mouse);
    void uiMouseLightning(typeWindowCovering& area,
                          bool&               open,
                          Mouse&              mouse,
                          LightningShape&     shape,
                          LightningColour&    colour,
                          LightningSize&      size);
    void uiFunctions(typeWindowCovering& area, bool& open, std::vector<std::string>& elements, const std::string& title);
    void uiTiles();
    void uiDoor(bool& open);
    void uiWarpsPopup();
    void uiWarps();
    void uiDoorPopup(); // Popup for door options
    void uiTexture(typeWindowCovering&                                                area,
                   bool&                                                              open,
                   const std::vector<std::pair<Graphics::TextureTypes, std::string>>& textures,
                   std::pair<Graphics::TextureTypes, std::string>&                    selectedTexture);
    void present(); // Render all graphic

  private:
    const int requestDimensionW; // Requested window width
    const int requestDimensionH; // Requested window height

    Common::typeScale mScale;

    bool mRun;
    bool mMapLoaded;
    bool mNewFile; // Start of a new project

    struct {
        float X;
        float Y;
    } mOffset;

    std::vector<std::string>             mMapFiles;
    std::unique_ptr<Common::InitHandler> mInitHandler;
    std::shared_ptr<Graphics::Graphics>  mGraphics;
    std::unique_ptr<Common::Perspective> mPerspective;

    std::vector<std::pair<Graphics::TextureTypes, std::string>> mTextures;        // All textures that we can use
    std::pair<Graphics::TextureTypes, std::string>              mSelectedTexture; // The selected texture

    // Events
    std::unique_ptr<Common::ActionManager>                                 mActionManager;
    std::list<std::function<bool(SDL_Event*)>>                             mEventWatcher; // List of all event to watch for
    std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>> mEvents;
    std::list<std::tuple<std::function<void(int)>, Utility::Timer>>        mProcessing;

    Utility::Timer mFPSTimer; // To lock fps

    SDL_Window*   pWindow;
    SDL_Renderer* pRenderer;
    // Mouse functions
    Mouse           mMouse;
    LightningColour mLightningColour;
    LightningShape  mLightningShape;
    LightningSize   mLightningSize;

    ImVec2 popupPosition;
    struct typeElementsCompare {
        bool operator()(const std::function<void()>& lhs, const std::function<void()>& rhs) const {
            return lhs.target_type().hash_code() < rhs.target_type().hash_code();
        }
    };
    std::unordered_map<std::string, typeWindowCovering>    mWindows;    // Contains the position and sizes of all windows
    std::unordered_map<std::string, bool>                  mWindowOpen; // True if a window is open
    std::vector<std::string>                               mElementsToHide;
    std::vector<std::string>                               mElementsToShow;
    std::unordered_map<std::string, std::function<void()>> mElements; // Contain all graphical elements
    std::set<std::function<void()>, typeElementsCompare>   mVisibleElements;
    bool                                                   mHideAllWindows; // True if all elements should be hidden
    std::string                                            mStringInput;
    bool                                                   showOverlay;
    bool                                                   showNumbers;
    bool                                                   showGrid;

    // Map data
    Level::File::typeHeaderData             fileHeader;
    Level::File::typeAssets                 fileAssets; // List of all the assets that exist in the current map.
    Level::File::typeSpawn                  fileSpawns;
    std::vector<Level::File::typeDoorsData> fileDoors; // Contains all doors
    std::vector<Level::File::typeWarpData>  fileWarps;

    std::vector<Tile*>                   editorTiles; // All tiles in the game.
    std::unordered_map<std::string, int> animationValuesBase;
    std::unordered_map<std::string, int> animationValuesTop;
    std::pair<int, int>                  clickedCoord;

    struct comparePair {
        bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
            if (lhs.first < rhs.first)
                return true;
            if (lhs.first > rhs.first)
                return false;
            return lhs.second < rhs.second;
        }
    };
    std::set<std::pair<int, int>, comparePair>      mLevelCoords; // A list of coordinates that is used
    std::vector<std::pair<SDL_Texture*, SDL_FRect>> mEdges;       // Edges for drawing area

    std::map<long int, std::shared_ptr<Common::Interrupt>> mInterrupts;
    std::vector<std::thread>                               mThreads;
};
}