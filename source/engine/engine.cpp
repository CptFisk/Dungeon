#include "engine/loading.hpp"

#include <common/handlers.hpp>
#include <engine/debug/fps.hpp>
#include <engine/engine.hpp>
#include <items/inventory.hpp>
#include <utility/file.hpp>
#include <utility/math.hpp>
#include <utility/textures.hpp>
#include <utility/trigonometry.hpp>

namespace Engine {

Engine::Engine()
  : pPlayerPosition(nullptr)
  , pPlayerTexture(nullptr)
  , pPlayerView(nullptr)
  , pWindow(nullptr)
  , pRenderer(nullptr)
  , pDarkness(nullptr)
  , mScale{}
  , mRun(true)
  , mVisibleUI(true)
  , mLevelLoaded(false)
  , mPlayerHealth(100)
  , mPlayerMaxHealth(100)
  , mPlayerEnergy(50)
  , mEvent{}
  , mMapCoordinate{}
  , mColour{}
  , mGameMode(GameMode::Inventory)
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

    // Clear projectiles
    for (auto& projectile : mProjectiles) {
        delete projectile;
    }
    // Clear floating textures
    for (auto& texture : mFloatingText) {
        delete texture;
    }
    mGraphics.reset(); // Kill graphics
    mInitHandler.shutdown();
}

Common::ActionManager&
Engine::getActionManager() {
    return *mActionManager;
}

Graphics::Graphics&
Engine::getGraphics(){
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
Engine::click() {
    switch (mGameMode) {
        case GameMode::Game: {
            const auto click = SDL_FPoint{ FLOAT(mActionManager->mouseX) + (mPerspective->mOffset.x / -1.0f),
                                           FLOAT(mActionManager->mouseY) + (mPerspective->mOffset.y / -1.0f) };
            const auto angle = Utility::getAngle(click, mPlayer->getPlayerCenter());
            mPlayerEnergy -= 3; // Reduce energy

            createProjectile(
              true, GET_ANIMATED("Fireball"), nullptr, Utility::offsetAngle(mPlayer->getPlayerCenter(), angle, 0), angle, 200, 0.75f, 10);
        } break;
        case GameMode::Inventory:
            mInventory->selectItemMouse(FLOAT(mActionManager->mouseX), FLOAT(mActionManager->mouseY));
            break;
        case GameMode::Menu:;
            break;
    }
}

void
Engine::movePlayer(Directions direction) {
    if (movement(mPlayer->getPlayerCenter(), direction))
        mPerspective->move(direction, mPlayer->move(direction));
    else
        mPlayer->setDirection(direction); // At least change direction
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
    mPlayer->spawn(9, 119);
    mPerspective->center(pPlayerPosition->x + 8.0f, pPlayerPosition->y + 8.0f);
    while (mRun) {
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
        mPerspective->render(*pPlayerTexture, *pPlayerView, pPlayerPosition);
        drawProjectiles();
        // Draw top layer
        drawLevel(mSegments.Top, mSegments.CurrentLayerTop);
        // Apply darkness
        drawDarkness();
        // Draw lightning
        drawLevel(mSegments.Lightning, mSegments.CurrentLayerLightning);
#pragma endregion

        switch (mGameMode) {
            case GameMode::Game: {
                for (auto drawData : mHealth->getIndicator()) {
                    SDL_RenderCopyF(pRenderer, drawData.Texture, drawData.Viewport, drawData.Position);
                }
                // Positions
                drawFloatingText();
            } break;
            case GameMode::Inventory: {
                for(auto data :  mInventory->getInventory()){
                    SDL_RenderCopyF(pRenderer, data.Texture, data.Viewport, data.Position);
                }

            } break;
        }
        /*
    #ifdef DEBUG_MODE
            // Display interaction area
            mPerspective->render(GET_GENERATED("0000FF")->getTexture(), nullptr, mPlayer->getInteractionArea());
            // Display player center
            SDL_FRect middle{ mPlayer->getPlayerCenter().x, mPlayer->getPlayerCenter().y, 1.0f, 1.0f };
            mPerspective->render(GET_GENERATED("A349A4")->getTexture(), nullptr, &middle);
            auto fpsPos = SDL_Rect{ 10, 10, 0, 0 };
            auto fps    = mGraphics->getSentence("8bit16", "FPS " + std::to_string(Debug::getFPS()));
            SDL_QueryTexture(fps, nullptr, nullptr, &fpsPos.w, &fpsPos.h);
            SDL_RenderCopy(pRenderer, fps, nullptr, &fpsPos);
            auto playerPos = SDL_Rect{ 10, 15 + fpsPos.h, 0, 0 };
            auto p         = mPlayer->getPlayerCoordinates();
            auto player    = mGraphics->getSentence("8bit16", std::to_string(p.x) + " " + std::to_string(p.y));
            SDL_QueryTexture(player, nullptr, nullptr, &playerPos.w, &playerPos.h);
            SDL_RenderCopy(pRenderer, player, nullptr, &playerPos);
    #endif
         */
        present();

        auto ticks = mFPSTimer.getTicks();
        if (ticks < 1000.0 / 60.0)
            SDL_Delay((1000 / 60.0) - ticks);
    }
}

void
Engine::projectiles() {

    for (auto it = mProjectiles.begin(); it != mProjectiles.end();) {
        bool removed = false;
        (*it)->move(); // Move it
        // Check monster for collision
        if ((*it)->getFriendly()) {
            for (auto it2 = mActiveMonsters.begin(); it2 != mActiveMonsters.end();) {
                if (Utility::isOverlapping((*it)->getProjectileCenter(), *(*it2)->getPosition())) {
                    const auto damage = (*it)->getDamage();
                    delete *it;                  // Free memory
                    it = mProjectiles.erase(it); // Move iterator
                    (*it2)->damageMonster(damage);
                    mFloatingText.push_back(
                      new Graphics::FloatingTexture(*(*it2)->getPosition(), nullptr, GET_GENERATED("000000")->getTexture(), 3000));
                    removed = true;
                    break;
                } else
                    ++it2;
            }
        } else {
            if (Utility::isOverlapping((*it)->getProjectileCenter(), *mPlayer->getTexturePosition())) {
                if ((mPlayerHealth -= (*it)->getDamage()) <= 0) {
                    std::cout << "Player died " << std::endl;
                }
                mHealth->updateIndicator();       // Update health bar
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
Engine::monsterActions() {

    auto state = mLuaManager->getState();
    for (auto& monster : mActiveMonsters) {
        const auto lua = monster->getLuaFile();

        mLuaManager->executeScript("scripts/monster/" + lua);

        lua_getglobal(state, "Interact");
        mLuaManager->createMonsterMetaTable(monster);

        if (lua_pcall(state, 1, 0, 0) != LUA_OK) {
            std::cerr << "Error: " << lua_tostring(state, -1) << std::endl;
            lua_pop(state, 1); // Remove error message from stack
        }
        const auto& data = monster->getMonster();
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
