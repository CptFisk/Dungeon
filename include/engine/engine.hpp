#pragma once
#include <common/include.hpp>
#include <engine/include.hpp>
#include <graphics/graphics.hpp>
#include <graphics/numbers.hpp>
#include <level/level.hpp>
#include <list>
#include <memory>
#include <monster/include.hpp>
#include <objects/include.hpp>
#include <player/indicator.hpp>
#include <player/player.hpp>
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
    void click(const float& x, const float& y); // Mouse click
    // Player movement
    void movePlayer(Directions direction);
    void setPlayerAction(Objects::State action);
    SDL_Event         mEvent;

  protected:
    void present();
    void monsters();
    void projectiles();

    void drawProjectiles();
    void drawNumbers();
    void drawLevel();

    void        addDarkness();
    std::thread spawnInterrupt(const long& time); // Spawn a thread

  private:
    bool              mRun;
    bool              mVisibleUI;
    Common::typeScale mScale;


    struct{
        Uint8 Red;
        Uint8 Green;
        Uint8 Blue;
    }Background;

    struct {
        float X;
        float Y;
    } offset;

    std::unique_ptr<Common::InitHandler> mInitHandler;
    std::unique_ptr<Player::Player>      mPlayer;
    std::shared_ptr<Graphics::Graphics>  mGraphics;
    std::unique_ptr<Level::Level>        mLevel;
    std::unique_ptr<Player::Indicator>   mHealth;
    std::unique_ptr<Player::Indicator>   mEnergy;
    std::unique_ptr<Common::Perspective> mPerspective;

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
    std::vector<std::thread>                       mThreads;
    std::map<long int, std::shared_ptr<Interrupt>> mInterrupts;

    // References to the player
    SDL_Texture** pPlayerTexture;
    SDL_FRect**   pPlayerView;
    SDL_FRect*    pPlayerPosition;
    int           mPlayerHealth;
    int           mPlayerEnergy;

    // Monster blueprints
    std::unordered_map<Monster::Monsters, Monster::BaseMonster*> mMonsters;
    std::vector<Monster::BaseMonster*>                           mActiveMonsters;

    // Visible numbers
    std::vector<Graphics::Number> mNumbers; // Visible numbers
};

}