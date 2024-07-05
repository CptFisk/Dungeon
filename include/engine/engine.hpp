#pragma once
#include <common/include.hpp>
#include <engine/include.hpp>
#include <graphics/graphics.hpp>
#include <graphics/numbers.hpp>
#include <level/file.hpp>
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
    SDL_Event mEvent;

  protected:
    std::mutex mMutex;
    void       present();
    void       monsters();
    void       projectiles();

    void drawProjectiles();
    void drawNumbers();
    void drawLevel();

    void        addDarkness();
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

    std::unique_ptr<Common::InitHandler> mInitHandler;
    std::unique_ptr<Player::Player>      mPlayer;
    std::shared_ptr<Graphics::Graphics>  mGraphics;
    std::unique_ptr<Player::Indicator>   mHealth;
    std::unique_ptr<Player::Indicator>   mEnergy;
    std::unique_ptr<Common::Perspective> mPerspective;
    std::unique_ptr<LoadingScreen>       mLoadingScreen;

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
    std::unordered_map<Monster::Monsters, Monster::BaseMonster*> mMonsters;
    std::vector<Monster::BaseMonster*>                           mActiveMonsters;

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

    /**
     * @brief Returns the position were the player should spawn
     */
    std::pair<uint8_t, uint8_t> getPlayerSpawn();

    // Segmentations
    void                 createSegments(const Level::File::typeAssets& assets);
    void                 addToSegment(const int& pos, const std::string& name);
    [[nodiscard]] size_t getSegment(const std::pair<int, int>& coord) const;

    void clearLoadedLevel();

    std::vector<typeSegment>           mSegments; // Level segments (generated)
    std::vector<Level::File::TileType> levelObjects;
    std::vector<Objects::Door*>        doors; // All doors on the map
    std::vector<Objects::Warp>         warps; // Warp locations

    // Level data
    bool                        mLevelLoaded;
    Level::File::typeHeaderData mHeader;
    std::string                 mFilename; // Name of the current loaded map
    int                         mCurrentLayer = 0;
    int                         mMaxLayers    = 0;
    static const int            segmentSizeX  = 64;
    static const int            segmentSizeY  = 64;

    Objects::TextBox* textBox;
};

}