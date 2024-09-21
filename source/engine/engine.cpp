#include "engine/loading.hpp"

#include <cmake.hpp>
#include <common/handlers.hpp>
#include <common/scale.hpp>
#include <engine/debug/fps.hpp>
#include <engine/engine.hpp>
#include <utility/file.hpp>
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
  , mPlayerEnergy(50)
  , mEvent{}
  , Background{} {}

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
    mGraphics.reset(); // Kill graphics
    mInitHandler.shutdown();
}

Common::ActionManager&
Engine::getActionManager() {
    return *mActionManager;
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

void
Engine::terminate() {
    mRun = false;
}

void
Engine::click() {
    const auto click = SDL_FPoint{ FLOAT(mActionManager->mouseX) + (mPerspective->mOffset.x / -1.0f),
                                   FLOAT(mActionManager->mouseY) + (mPerspective->mOffset.y / -1.0f) };
    const auto angle = Utility::getAngle(click, mPlayer->getPlayerCenter());
    mPlayerEnergy -= 3; // Reduce energy
    Objects::typeProjectileStruct setup{ GET_ANIMATED("Fireball"), GET_GENERATED("RedCircle")->getTexture(), angle, 100, 5.0 };
    mProjectiles.push_back(new Objects::Projectile(setup, { pPlayerPosition->x, pPlayerPosition->y }, pRenderer, mParticles));
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
        // Apply background color
        SDL_SetRenderDrawColor(pRenderer, Background.Red, Background.Green, Background.Blue, SDL_ALPHA_OPAQUE);
        drawLevel(mSegments.Bottom, mSegments.CurrentLayerBottom);
        // Show interaction box during debug

        // Display interaction area
        mPerspective->render(GET_GENERATED("0000FF")->getTexture(), nullptr, mPlayer->getInteractionArea());
        // Display player center
        SDL_FRect middle{ mPlayer->getPlayerCenter().x, mPlayer->getPlayerCenter().y, 1.0f, 1.0f };
        mPerspective->render(GET_GENERATED("A349A4")->getTexture(), nullptr, &middle);

        monsters();
        mPerspective->render(*pPlayerTexture, *pPlayerView, pPlayerPosition); // Draw our cute hero
        projectiles();
        drawProjectiles();
        drawLevel(mSegments.Top, mSegments.CurrentLayerTop);
        drawDarkness();
        // Positions
        drawNumbers();

        drawLevel(mSegments.Lightning, mSegments.CurrentLayerLightning);
        for (auto drawData : mHealth->getIndicator()) {
            SDL_RenderCopyF(pRenderer, drawData.Texture, drawData.Viewport, drawData.Position);
        }

#ifdef DEBUG_MODE
        auto fpsPos = SDL_Rect{ 10, 10, 0, 0 };
        auto fps    = mGraphics->getSentence("8bit16", "FPS: " + std::to_string(Debug::getFPS()));
        SDL_QueryTexture(fps, nullptr, nullptr, &fpsPos.w, &fpsPos.h);
        SDL_RenderCopy(pRenderer, fps, nullptr, &fpsPos);
        auto playerPos = SDL_Rect{ 10, 15 + fpsPos.h, 0, 0 };
        auto p         = mPlayer->getPlayerCoordinates();
        auto player    = mGraphics->getSentence("8bit16", std::to_string(p.x) + " " + std::to_string(p.y));
        SDL_QueryTexture(player, nullptr, nullptr, &playerPos.w, &playerPos.h);
        SDL_RenderCopy(pRenderer, player, nullptr, &playerPos);
#endif

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
        for (auto it2 = mActiveMonsters.begin(); it2 != mActiveMonsters.end();) {
            if (Utility::isOverlapping(*(*it)->getPosition(), *(*it2)->getPosition())) {
                const auto damage = (*it)->getDamage();
                delete *it;                  // Free memory
                it = mProjectiles.erase(it); // Move iterator
                (*it2)->damageMonster(damage);
                // Display the damage
                /*
                mNumbers.push_back(
                  Graphics::Number({ (*it2)->getPosition()->x, (*it2)->getPosition()->y }, damage, 100, *GET_SIMPLE("NumbersWhite"), 0.5f));
                  */
                removed = true;
                break;
            } else
                ++it2;
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
Engine::monsters() {
    for (auto it = mActiveMonsters.begin(); it != mActiveMonsters.end();) {
        if ((*it)->getState() == Objects::DEAD) {
            it = mActiveMonsters.erase(it);
        } else {
            const auto data = (*it)->getMonster();
            mPerspective->render(data.Texture, data.Viewport, data.Position);
            ++it;
        }
    }
}

void
Engine::drawProjectiles() {
    for (const auto& projectile : mProjectiles) {
        const auto lightning = projectile->getLightning();
        const auto object    = projectile->getProjectile();
        if (lightning.Texture != nullptr)
            mPerspective->render(lightning.Texture, lightning.Viewport, lightning.Position);
        mPerspective->renderRotated(object.Texture, object.Viewport, object.Position, object.Angle);
    }
    for (auto& projectile : mParticles->getDrawData()) {
        mPerspective->render(projectile.Texture, projectile.Viewport, projectile.Position);
    }
}

void
Engine::drawNumbers() {
    for (auto it = mNumbers.begin(); it != mNumbers.end();) {
        if ((*it).expired())
            it = mNumbers.erase(it);
        else {
            auto data = (*it).getNumber();
            for (auto& [position, viewport] : data.Visuals) {
                mPerspective->render(data.Texture, viewport, &position);
            }
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
}
