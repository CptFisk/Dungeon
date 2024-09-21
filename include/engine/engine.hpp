#pragma once
#include <common/include.hpp>
#include <common/initializer/initializer.hpp>
#include <common/segment.hpp>
#include <engine/include.hpp>
#include <graphics/graphics.hpp>
#include <graphics/numbers.hpp>
#include <list>
#include <memory>
#include <monster/include.hpp>
#include <mutex>
#include <object/include.hpp>
#include <player/indicator.hpp>
#include <player/player.hpp>
#include <set>
#include <string>
#include <thread>
#include <ui/textbox.hpp>
#include <utility/timer.hpp>
#include <utility>

namespace Engine {
class Engine {
  public:
    Engine();  // Basic constructor
    ~Engine(); // Cleanup

    void startup(); // Load all functions related to startup
    void mainLoop();

    Common::ActionManager& getActionManager();

    [[maybe_unused]] std::list<std::function<bool(SDL_Event*)>>&                             getEventList(); // Get the list of events
    [[maybe_unused]] std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>>& getEvents();    // Get the list of events
    [[maybe_unused]] std::list<std::tuple<std::function<void(int)>, Utility::Timer>>&        getProcessing();

    void terminate();
    void click(); // Mouse click
    // Player movement
    void      movePlayer(Directions direction);
    void      setPlayerAction(Objects::State action);
    void      resetPlayerMomentum();
    void      interact();
    void      setDarkness(const unsigned int& v);
    bool      movementWalls(const SDL_FPoint& other, const float& x, const float& y);
    SDL_Event mEvent;

  protected:
    std::mutex mMutex;
    void       present();
    void       monsters();
    void       projectiles();

    void drawProjectiles();
    void drawNumbers();
    void drawLevel(Common::typeSegmentData& data, const int& currentLayer);

    void        drawDarkness();
    std::thread spawnInterrupt(const long& time); // Spawn a thread

  private:
    bool              mRun;
    bool              mVisibleUI;
    Common::typeScale mScale;

    struct {
        Uint8 Red;
        Uint8 Green;
        Uint8 Blue;
    } Background;

    struct {
        float X;
        float Y;
    } offset;

    Common::InitHandler                  mInitHandler;
    std::unique_ptr<Player::Player>      mPlayer;
    std::shared_ptr<Graphics::Graphics>  mGraphics;
    std::unique_ptr<Player::Indicator>   mHealth;
    std::unique_ptr<Player::Indicator>   mEnergy;
    std::unique_ptr<Common::Perspective> mPerspective;
    std::unique_ptr<LoadingScreen>       mLoadingScreen;
    std::unique_ptr<UI::Textbox>         mTextbox;

    // Events
    std::unique_ptr<Common::ActionManager>                                 mActionManager;
    std::list<std::function<bool(SDL_Event*)>>                             mEventWatcher; // List of all event to watch for
    std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>> mEvents;
    std::list<std::tuple<std::function<void(int)>, Utility::Timer>>        mProcessing;

    std::vector<Objects::Projectile*>  mProjectiles; // All projectiles
    std::shared_ptr<Objects::Particle> mParticles;

    SDL_Window*   pWindow;
    SDL_Renderer* pRenderer;

    Utility::Timer mFPSTimer; // To lock fps

    // Threads and interrupts
    std::vector<std::thread>                               mThreads;
    std::map<long int, std::shared_ptr<Common::Interrupt>> mInterrupts;
    std::thread                                            mLoading;
    // References to the player
    SDL_Texture** pPlayerTexture;
    SDL_Rect**    pPlayerView;
    SDL_FRect*    pPlayerPosition;
    int           mPlayerHealth;
    int           mPlayerEnergy;

    // Monster blueprints
    void                                                     createMonsters();
    std::unordered_map<Monster::Type, Monster::BaseMonster*> mMonsters;
    std::vector<Monster::BaseMonster*>                       mActiveMonsters;

    // Visible numbers
    std::vector<Graphics::Number> mNumbers; // Visible numbers

    /**
     * @breif Check if movement is allowed, or if it collides with other objects
     * @param other Object to check with
     * @return true = movement allowed
     */
    bool movement(const SDL_FRect& other, const Directions& direction);
    bool movement(const SDL_FPoint& other, const Directions& direction);
    // Load a level
    void loadLevel(const std::string& filename);
    void clearLoadedLevel();

    /**
     * @brief A vector that contains all the segments for the map.
     * @example Wanting to draw animation frames 0 for bottom layer should be this:
     * @example for(auto& frame : mSegments.Bottom){
     * @example render(frame[0]);
     * @example }
     */
    Common::typeSegment                     mSegments;
    std::vector<std::bitset<8>>             levelObjects;
    std::vector<Objects::Door*>             doors; // All doors on the map
    std::unordered_map<int, Objects::Warp*> warp;  // Warp locations

    // Level data
    bool                  mLevelLoaded;
    std::string           mFilename; // Name of the current loaded map
    static const int      segmentSizeX = 128;
    static const int      segmentSizeY = 128;
    SDL_Texture*          pDarkness;
};

extern Engine engine;

}