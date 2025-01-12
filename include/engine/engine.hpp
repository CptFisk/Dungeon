#pragma once
#include <common/include.hpp>
#include <common/initializer/initializer.hpp>
#include <common/segment.hpp>
#include <engine/include.hpp>
#include <engine/lua/luaManager.hpp>
#include <graphics/floatingText.hpp>
#include <graphics/graphics.hpp>
#include <items/definition.hpp>
#include <items/inventory.hpp>
#include <items/item.hpp>
#include <list>
#include <memory>
#include <monster/include.hpp>
#include <mutex>
#include <npc/include.hpp>
#include <object/include.hpp>
#include <player/player.hpp>
#include <set>
#include <string>
#include <thread>
#include <ui/textbox.hpp>
#include <ui/userInterface.hpp>
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
    Graphics::Graphics&    getGraphics();

    [[maybe_unused]] std::list<std::function<bool(SDL_Event*)>>&                             getEventList(); // Get the list of events
    [[maybe_unused]] std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>>& getEvents();    // Get the list of events
    [[maybe_unused]] std::list<std::tuple<std::function<void(int)>, Utility::Timer>>&        getProcessing();
    [[maybe_unused]] GameMode getGameMode() const; // Return the current mode the game is operating in

    void click();     // Mouse click
    void changeMode(const GameMode& mode);
    void back();      // Used to close current view, or terminate
#pragma region Player
    void            movePlayer(Direction direction);
    void            setPlayerAction(Objects::State action);
    Player::Player& getPlayer();
#pragma endregion
    void resetPlayerMomentum();
    void interact();
    void setDarkness(const unsigned int& v);
#pragma region LUA functions
    /**
     * @brief Check for collision against a wall or similar object
     * @param x In-game coordinate
     * @param y In-game coordinate
     * @param mask See global.hpp for mask settings
     * @return True if movement is possible
     */
    bool wallCheck(const float& x, const float& y, const long unsigned int& mask);
    /**
     * @brief Spawns a new particle
     * @param friendly False if it can hurt the player, otherwise true
     * @param texture Texture for projectile
     * @param effect Texture for effect
     * @param startPoint Start position for the projectile
     * @param angle Angle to fly
     * @param duration How long the projectile exist
     * @param velocity Speed for the projectile
     * @param damage How much it will hurt
     */
    void createProjectile(const bool&                friendly,
                          Graphics::AnimatedTexture* texture,
                          Graphics::AnimatedTexture* effect,
                          const SDL_FPoint&          startPoint,
                          const double&              angle,
                          const int&                 duration,
                          const float&               velocity,
                          const int&                 damage);
#pragma endregion
    SDL_Event mEvent;
    void      terminate();

  protected:
    std::mutex mMutex;
    void       present();
    void       units();
    void       projectiles();
    /**
     * @brief Function used to handle melee attacks
     */
    void meleeAttack();

    void drawProjectiles();
    void drawFloatingText();
    void drawLevel(Common::typeSegmentData& data, const int& currentLayer);

    void        drawDarkness();
    std::thread spawnInterrupt(const long& time); // Spawn a thread

  private:
    bool              mRun;
    Common::typeScale mScale;
    GameMode          mGameMode; // Current operating mode
    struct {
        float X;
        float Y;
    } offset;

    Common::InitHandler                 mInitHandler;
    std::shared_ptr<Player::Player>     mPlayer;
    std::shared_ptr<Graphics::Graphics> mGraphics;
    std::unique_ptr<Common::Perspective> mPerspective;
    std::unique_ptr<LoadingScreen>       mLoadingScreen;
    std::unique_ptr<UI::Textbox>         mTextbox;
    std::unique_ptr<Lua::LuaManager>     mLuaManager;
    std::unique_ptr<Items::Inventory>    mInventory;
    /**
     * @brief Handle the visibility of all elements in the game
     */
    std::unique_ptr<UI::UserInterface> mUserInterface;

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
#pragma region Player
    SDL_Texture*&         pPlayerTexture;
    SDL_Rect*&            pPlayerView;
    SDL_FRect&            pPlayerPosition;
    const Objects::State* pPlayerAction;

#pragma endregion

#pragma region Items
    /**
     * @brief Function that is used to populate @ref mItems
     */
    void                                        createItems();
    std::unordered_map<Items::Id, Items::Item*> mItems;
#pragma endregion
#pragma region Monsters
    /**
     * @brief Function that is used to populate @ref mMonsters
     */
    void createMonsters();
    void monsterActions();
    /**
     * @brief Map that contains a blue-print for each monster. The units is added to the map through the function @ref createMonsters().
     */
    std::unordered_map<Monster::Type, Monster::BaseMonster*> mMonsters;
    /**
     * @brief Map that contains all ACTIVE units that is alive on the map, this vector should be cleared once a map is reloaded.
     */
    std::vector<Monster::BaseMonster*> mActiveMonsters;
    /**
     * @brief Highest value that we need to loop inside @ref mActiveMonsters
     */
    size_t mMonsterIndex;
#pragma endregion
#pragma region NPC
    /**
     * @brief Function that is used to populate @ref mNPC
     */
    void createNPC();
    /**
     * @brief Map that contains a blue-print for each NPC. The units is added to the map through the function @ref createNPC().
     */
    std::unordered_map<NPC::Type, NPC::BaseNPC*> mNPCs;
    /**
     * @brief Map that contains all ACTIVE NPC that is alive on the map, this vector should be cleared once a map is reloaded.
     */
    std::vector<NPC::BaseNPC*> mActiveNPCs;

#pragma endregion
    std::vector<Graphics::FloatingTexture*> mFloatingText; // Floating texts

    /**
     * @breif Check if movement is allowed, or if it collides with other objects
     * @param other Object to check with
     * @return true = movement allowed
     */
    bool movement(const SDL_FPoint& other, const SDL_FPoint& vector, const double& angle);
    bool movement(const SDL_FRect& other, const Orientation& direction);
    bool movement(const SDL_FPoint& other, const Orientation& direction);
    bool wallCheck(const SDL_FPoint& other, const float& x, const float& y, const long unsigned int& mask, bool playerCheck);

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
    Common::type3DMapCoordinate mMapCoordinate;
    Common::typeColour          mColour;

    bool         mLevelLoaded;
    std::string  mFilename; // Name of the current loaded map
    SDL_Texture* pDarkness;
};

extern Engine engine;

}