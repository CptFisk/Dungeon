#pragma once
#include <engine/include.hpp>
#include <graphics/graphics.hpp>
#include <list>
#include <memory>
#include <objects/include.hpp>
#include <player/player.hpp>
#include <string>
#include <thread>
#include <timer.hpp>
#include <utility>
#include <world/level.hpp>

namespace Engine {
class Engine {
  public:
    Engine();  // Basic constructor
    ~Engine(); // Cleanup

    void startup(); // Load all functions related to startup
    void mainLoop();

    ActionManager& getActionManager();

    void addEventWatcher(std::function<bool(SDL_Event*)> handler);                    // Add event to listen
    void queueEventHandler(Uint32 evenType, std::function<bool(SDL_Event*)> handler); // Add event in queue
    void queueProcessHandler(std::function<void(int)> handler);                       // Add process to handle in queue
    void terminate();
    void click(const float& x, const float& y); // Mouse click
    // Player movement
    void movePlayer(Directions direction);
    void setPlayerAction(Objects::ObjectAction action);

  protected:
    void present();
    void calculateScale(); // Calculate the scale of each tile to match screen dimensions
    void projectiles();

    void        addDarkness();
    std::thread spawnInterrupt(const long& time); // Spawn a thread

  private:
    bool  mRun;
    Scale mScale;

    std::unique_ptr<InitHandler>        mInitHandler;
    std::unique_ptr<Player::Player>     mPlayer;
    std::shared_ptr<Graphics::Graphics> mGraphics;
    std::shared_ptr<Level>              mLevel;
    // Events
    std::unique_ptr<ActionManager>             mActionManager;
    std::list<std::function<bool(SDL_Event*)>> mEventWatcher; // List of all event to watch for
    std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>> mEvents;
    std::list<std::tuple<std::function<void(int)>, Timer>>                 mProcessing;

    std::vector<Objects::Projectile*> mProjectiles; // All projectiles
    SDL_Window*                       pWindow;
    SDL_Renderer*                     pRenderer;

    Timer mFPSTimer; // To lock fps

    // Threads and interrupts
    std::vector<std::thread>                       mThreads;
    std::map<long int, std::shared_ptr<Interrupt>> mInterrupts;

    // References to the player
    SDL_Texture** pPlayerTexture;
    SDL_FRect**   pPlayerView;
    SDL_FRect*    pPlayerPosition;
};

}