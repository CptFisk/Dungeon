#include "engine/loading.hpp"

#include <common/handlers.hpp>
#include <common/initializer/sdl.hpp>
#include <common/initializer/sdlTTF.hpp>
#include <engine/engine.hpp>
#include <items/inventory.hpp>
#include <utility/file.hpp>
#include <utility/functions.hpp>
#include <utility/orientation.hpp>
#include <utility/sdl.hpp>
#include <utility/textures.hpp>
#include <utility/trigonometry.hpp>
namespace Engine {

Engine::Engine()
  : mInitHandler(std::vector<std::shared_ptr<Common::Initializer>>{
      std::make_shared<Common::SDLInitializer>(pWindow, pRenderer, 1920, 1080, false, "Vera adventure"),
      std::make_shared<Common::SDLTTFInitializer>() })
  , mActionManager(std::make_unique<Common::ActionManager>(pRenderer, mScale, offset.X, offset.Y))
  , mGraphics(std::make_shared<Graphics::Graphics>(pRenderer))
  , mPlayer(std::make_shared<Player::Player>())
  , pPlayerPosition(mPlayer->getTexturePosition())
  , pPlayerTexture(mPlayer->getTexture())
  , pPlayerView(mPlayer->getTextureViewport())
  , mInventory(std::make_unique<Items::Inventory>())
  , mUserInterface(std::make_unique<UI::UserInterface>(mGraphics,
                                                       pRenderer,
                                                       mScale,
                                                       mPlayer->getSoulCount(),
                                                       mInventory->getSlots(),
                                                       mPlayer->getPlayerStats(),
                                                       mInventory->getItemStats()))
  , pDarkness(nullptr)
  , pPlayerAction(nullptr)
  , mScale{}
  , mRun(true)
  , mLevelLoaded(false)
  , mMapCoordinate{}
  , mColour{}
  , mGameMode(GameMode::Game)
  , mLuaManager(std::make_unique<Lua::LuaManager>()) {}

Engine::~Engine() {
    // De-spawn all threads
    for (auto& thread : mThreads) {
        thread.join();
    }
    if (mLevelLoaded)
        clearLoadedLevel();
    // Kill all cute monsters
    for (auto monster : mActiveMonsters) {
        delete monster;
    }
    for (auto& [name, monster] : mMonsters)
        delete monster; // Kill the baby
    // Clear items
    for (auto& [id, item] : mItems)
        delete item;
    // Clear projectiles
    for (auto& projectile : mProjectiles) {
        delete projectile;
    }
    // Clear floating textures
    for (auto& texture : mFloatingText) {
        delete texture;
    }
    mUserInterface.reset();
    mGraphics.reset(); // Kill graphics
    mInitHandler.shutdown();
}

Common::ActionManager&
Engine::getActionManager() {
    return *mActionManager;
}

Graphics::Graphics&
Engine::getGraphics() {
    return *mGraphics;
}

std::list<std::function<bool(SDL_Event*)>>&
Engine::getEventList() {
    return mEventWatcher;
}

std::unordered_map<Uint32, std::list<std::function<bool(SDL_Event*)>>>&
Engine::getEvents() {
    return mEvents;
}

std::list<std::tuple<std::function<void(int)>, Utility::Timer>>&
Engine::getProcessing() {
    return mProcessing;
}

[[maybe_unused]] GameMode
Engine::getGameMode() const {
    return mGameMode;
}

void
Engine::terminate() {
    mRun = false;
}

void
Engine::changeMode(const GameMode& mode) {
    switch (mGameMode) {
        case GameMode::Game:
            mGameMode = mode;
            break;
        case GameMode::Inventory:
            if (mode == GameMode::Inventory)
                mGameMode = GameMode::Game;
            else
                mGameMode = mode;
            break;
        case GameMode::Attributes:
            if (mode == GameMode::Attributes)
                mGameMode = GameMode::Game;
            else
                mGameMode = mode;
            break;
    }
}

void
Engine::back() {
    switch (mGameMode) {
        case GameMode::Game:
            terminate();
            break;
        case GameMode::Inventory:
            mGameMode = GameMode::Game;
            break;
        default:
            break;
    }
}

void
Engine::click() {
    switch (mGameMode) {
        case GameMode::Game: {
            const auto click = Utility::PointToFPoint(mActionManager->getMouseRelative());
            const auto angle = Utility::getAngle(click, mPlayer->getPlayerCenter());
            if (mInventory->getLeftWeapon() != Items::WeaponType::None)
                mPlayer->doAttack(Utility::getOrientation(angle));
            /*
            createProjectile(
              true, GET_ANIMATED("Fireball"), nullptr, Utility::offsetAngle(mPlayer->getPlayerCenter(), angle, 0), angle, 200, 0.75f, 10);
              */
        } break;
        case GameMode::Inventory: {
            const auto& index = mUserInterface->selectItemMouse(Utility::PointToFPoint(mActionManager->getMouseAbsolute()));
            if (index.has_value()) {
                if (mInventory->selectItem(index.value(), mUserInterface->getSelectorVisible()))
                    mUserInterface->updateAttributes();
            }
        } break;
        case GameMode::Menu:;
            break;
    }
}

void
Engine::movePlayer(Direction direction) {
    float angleOffset = {};
    switch (direction) {
        case Right:
            angleOffset = 90;
            break;
        case Backward:
            angleOffset = 180;
            break;
        case Left:
            angleOffset = 270;
            break;
        default:
            break;
    }
    /*
     * Get angle from mouse position. 0 degree is right, 90 down, 180 left and 270 up
     */
    const auto       angle       = Utility::getAngle(mActionManager->getMouseRelative(), mPlayer->getPlayerCenter()) + angleOffset;
    const auto       vector      = Utility::calculateVector(angle, 1.0f);
    const auto       orientation = Utility::getOrientation(angle);
    const SDL_FPoint invVector   = { vector.x / -1.0f, vector.y / -1.0f };
    if (movement(mPlayer->getPlayerCenter(), vector, angle)) {
        mPlayer->move(vector, orientation);
        mPerspective->move(invVector);
    }
    /*
    if (movement(mPlayer->getPlayerCenter(), direction))
        mPerspective->move(direction, mPlayer->move(direction));
    else
        mPlayer->setDirection(direction); // At least change direction
    */
}

void
Engine::setPlayerAction(Objects::State action) {
    mPlayer->setAction(action);
}

Player::Player&
Engine::getPlayer() {
    return *mPlayer;
}

void
Engine::resetPlayerMomentum() {
    mPlayer->resetMomentum();
}

void
Engine::interact() {
    auto interactionArea = mPlayer->getInteractionArea();
    for (auto& door : doors) {
        if (Utility::isOverlapping(*interactionArea, door->getPosition())) {
            door->interact(true);
            break;
        }
    }
}

void
Engine::mainLoop() {
    auto      t   = GET_ANIMATED("Soul");
    SDL_FRect pos = { 16, 16, 16, 16 };
    mPlayer->spawn(9, 119);
    mPerspective->center(pPlayerPosition.x + 8.0f, pPlayerPosition.y + 8.0f);

    while (mRun) {
        // Sort monster list
        for (auto& monster : mActiveMonsters)
            monster->setPlayerDistance(Utility::getDistance(mPlayer->getPlayerCenter(), monster->getCenter()));
        Utility::sortBy(mActiveMonsters, [&](const Monster::BaseMonster* monster) { return monster->getPlayerDistance(); });

        mMonsterIndex = mActiveMonsters.size(); // Start value
        // Finding the threshold for monster that is close to the player
        for (auto i = 0; i < mActiveMonsters.size(); i++) {
            if (mActiveMonsters[i]->getPlayerDistance() > 20.0f) {
                mMonsterIndex = i;
                break;
            }
        }

        mFPSTimer.start();
        SDL_SetRenderTarget(pRenderer, nullptr);
        SDL_RenderClear(pRenderer);
        while (SDL_PollEvent(&mEvent)) {
            bool accepted = true;

            for (auto& handler : mEventWatcher) {
                if (!handler(&mEvent)) {
                    accepted = false;
                    break;
                }
            }

            if (accepted && mEvents.find(mEvent.type) != mEvents.end()) {
                auto handlers = mEvents[mEvent.type];
                for (auto& handler : handlers) {
                    if (!handler(&mEvent))
                        break;
                }
            }
        }

        for (auto& [handler, timer] : mProcessing) {
            handler(timer.getTicks());
            timer.start();
        }
#pragma region Game events
        // Call all monster and nps
        projectiles();
#pragma endregion
#pragma region Common draws
        // Apply background color
        SDL_SetRenderDrawColor(pRenderer, mColour.BackgroundRed, mColour.BackgroundGreen, mColour.BackgroundBlue, SDL_ALPHA_OPAQUE);
        drawLevel(mSegments.Bottom, mSegments.CurrentLayerBottom);

        monsterActions();
        units();

        // Draw our cute hero
        mPerspective->render(pPlayerTexture, pPlayerView, &pPlayerPosition);
        if (mPlayer->isAttacking())
            mPerspective->render(mPlayer->getSweepTexture(), mPlayer->getSweepViewport(), mPlayer->getInteractionArea());
        drawProjectiles();
        meleeAttack(); // Handle melee attack
        // Draw top layer
        drawLevel(mSegments.Top, mSegments.CurrentLayerTop);
        // Apply darkness
        drawDarkness();
        // Draw lightning
        drawLevel(mSegments.Lightning, mSegments.CurrentLayerLightning);
#pragma endregion

        switch (mGameMode) {
            case GameMode::Game:
                for (auto data : mUserInterface->getIndicators())
                    SDL_RenderCopyF(pRenderer, data.Texture, data.Viewport, data.Position);
                // Positions
                drawFloatingText();
                break;
            case GameMode::Inventory:
                for (auto data : mUserInterface->getInventory()) {
                    SDL_RenderCopyF(pRenderer, data.Texture, data.Viewport, data.Position);
                }
                break;
            case GameMode::Attributes:
                for (auto data : mUserInterface->getAttributes()) {
                    SDL_RenderCopyF(pRenderer, data.Texture, data.Viewport, data.Position);
                }
                break;
        }
        SDL_RenderCopyF(pRenderer, t->getTexture(), t->getAnimatedViewport(), &pos);
        present();
    }
}

void
Engine::projectiles() {
    for (auto it = mProjectiles.begin(); it != mProjectiles.end();) {
        bool removed = false;
        (*it)->move(); // Move it
        // Check monster for collision
        if ((*it)->getFriendly()) {
            const auto monsterEnd = mActiveMonsters.begin() + mMonsterIndex;
            for (auto monsterIt = mActiveMonsters.begin(); monsterIt != monsterEnd;) {
                if (Utility::isOverlapping((*it)->getProjectileCenter(), *(*monsterIt)->getPosition())) {
                    const auto damage = (*it)->getDamage();
                    delete *it;                  // Free memory
                    it = mProjectiles.erase(it); // Move iterator
                    (*monsterIt)->damageMonster(damage);
                    removed = true;
                    break;
                } else
                    ++monsterIt;
            }
        } else {
            if (Utility::isOverlapping((*it)->getProjectileCenter(), mPlayer->getTexturePosition())) {
                /*
                if ((mPlayerHealth -= (*it)->getDamage()) <= 0) {
                    std::cout << "Player died " << std::endl;
                }
                 */
                // mHealth->updateIndicator();       // Update health bar
                delete *it;                       // Free memory
                it      = mProjectiles.erase(it); // Move iterator
                removed = true;
            }
        }
        if (!removed) {
            if ((*it)->getNewDuration() < 0) {
                delete *it;
                it = mProjectiles.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void
Engine::meleeAttack() {
    // If we dont attack, simply return
    if (!mPlayer->isAttacking())
        return;

    const auto itEnd = mActiveMonsters.begin() + mMonsterIndex;
    const auto area  = *mPlayer->getInteractionArea();
    for (auto it = mActiveMonsters.begin(); it != itEnd;) {
        auto& monster = (*it);
        if (Utility::isOverlapping(monster->getCenter(), area)) {
            monster->damageMonster(100);
            break;
        }
        ++it;
    }
}

void
Engine::monsterActions() {
    auto state = mLuaManager->getState();
    for (auto i = 0; i < mMonsterIndex; i++) {
        const auto lua = mActiveMonsters[i]->getLuaFile();
        mLuaManager->executeScript("scripts/monster/" + lua);
        lua_getglobal(state, "Interact");
        mLuaManager->createMonsterMetaTable(mActiveMonsters[i]);

        if (lua_pcall(state, 1, 0, 0) != LUA_OK) {
            std::cerr << "Error: " << lua_tostring(state, -1) << std::endl;
            lua_pop(state, 1); // Remove error message from stack
        }
        const auto& data = mActiveMonsters[i]->getMonster();
        mPerspective->render(data.Texture, data.Viewport, data.Position);
    }
}

void
Engine::units() {
    // Npc cant die, at least for now
    for (auto& npc : mActiveNPCs) {
        const auto& data = npc->getNpc();
        mPerspective->render(data.Texture, data.Viewport, data.Position);
    }
}

void
Engine::drawProjectiles() {
    for (const auto& projectile : mProjectiles) {
        const auto& object = projectile->getProjectile();
        mPerspective->renderRotated(object.Texture, object.Viewport, object.Position, object.Angle);
        if (projectile->effectsEnabled()) {
            const auto& effect = projectile->getEffect();
            mPerspective->render(effect.Texture, effect.Viewport, effect.Position);
        }
    }
    for (auto& projectile : mParticles->getDrawData()) {
        mPerspective->render(projectile.Texture, projectile.Viewport, projectile.Position);
    }
}

void
Engine::drawFloatingText() {
    for (auto it = mFloatingText.begin(); it != mFloatingText.end();) {
        if ((*it)->expired()) {
            delete (*it);
            it = mFloatingText.erase(it);
        } else {
            auto data = (*it)->getFloatingText();
            // SDL_RenderCopyF(pRenderer, data.Texture, data.Viewport, data.Position);
            mPerspective->render(data.Texture, data.Viewport, data.Position);
            ++it;
        }
    }
}

void
Engine::drawLevel(Common::typeSegmentData& data, const int& currentLayer) {
    std::lock_guard<std::mutex> lock(mMutex);
    mPerspective->render(data.Layers[currentLayer], nullptr, &data.Position);
}

std::thread
Engine::spawnInterrupt(const long& time) {
    auto thread = std::thread([&]() {
        auto interrupt    = std::make_shared<Common::Interrupt>(time, mRun);
        mInterrupts[time] = interrupt;
        interrupt->execute();
    });
    return thread;
}

void
Engine::present() {
    SDL_RenderPresent(pRenderer);
}

void
Engine::createProjectile(const bool&                friendly,
                         Graphics::AnimatedTexture* texture,
                         Graphics::AnimatedTexture* effect,
                         const SDL_FPoint&          startPoint,
                         const double&              angle,
                         const int&                 duration,
                         const float&               velocity,
                         const int&                 damage) {

    mProjectiles.push_back(new Objects::Projectile(friendly, // Is cast by the player
                                                   texture,  // Animated texture
                                                   effect,   // Effect
                                                   startPoint,
                                                   angle,        // Angle
                                                   duration,     // Duration
                                                   velocity,     // Velocity
                                                   damage,       // Damage
                                                   mParticles)); // Particles
}
}
