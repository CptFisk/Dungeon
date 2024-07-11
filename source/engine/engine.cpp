#include "engine/loading.hpp"

#include <cmake.hpp>
#include <common/handlers.hpp>
#include <common/scale.hpp>
#include <engine/engine.hpp>
#include <utility/file.hpp>
#include <utility/textures.hpp>
#include <utility/trigonometry.hpp>

namespace Engine {

Engine::Engine()
  : mInitHandler(std::make_unique<Common::InitHandler>())
  , pPlayerPosition(nullptr)
  , pPlayerTexture(nullptr)
  , pPlayerView(nullptr)
  , pWindow(nullptr)
  , pRenderer(nullptr)
  , mScale{}
  , mRun(true)
  , mVisibleUI(true)
  , mLevelLoaded(false)
  , mPlayerHealth(100)
  , mPlayerEnergy(50)
  , mEvent{}
  , Background{}
  , mSegments{}
  , mActionManager(std::make_unique<Common::ActionManager>()) {}

Engine::~Engine() {
    if (mLevelLoaded)
        clearLoadedLevel();
    mGraphics.reset(); // Kill graphics
    // Kill all cute monsters
    for (auto& [name, monster] : mMonsters)
        delete monster; // Kill the baby

    // Clear projectiles
    for (auto& projectile : mProjectiles) {
        delete projectile;
    }
    // De-spawn all threads
    for (auto& thread : mThreads) {
        thread.join();
    }
    mInitHandler->shutdown();
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
Engine::startup() {
    // Starting interrupts
    mThreads.push_back(spawnInterrupt(10));
    mThreads.push_back(spawnInterrupt(100));
    mThreads.push_back(spawnInterrupt(500));

    mInitHandler->addInitializer(std::make_shared<Common::SDLInitializer>(pWindow, pRenderer, 1280, 960, "Vera adventure"));
    mInitHandler->startup();
    /*
    mLoadingScreen = std::make_unique<LoadingScreen>(pRenderer, mMutex);

    mLoading = std::thread([&]() {
        mLoadingScreen->run();
    });
    */
    Common::calculateGameScale(mScale, pWindow);
    SDL_RenderSetLogicalSize(pRenderer, 256, 192);
    mActionManager->bindRenderer(&pRenderer); // Bind the renderer

    // Generate graphics
    mGraphics = std::make_shared<Graphics::Graphics>(pRenderer);
    mGraphics->init();

    loadLevel("555.map");
    SDL_RenderClear(pRenderer);

    mPlayer = std::make_unique<Player::Player>();

    mHealth =
      std::make_unique<Player::Indicator>(mVisibleUI, mPlayerHealth, 36.0f, pRenderer, *GET_ANIMATED("Heart"), *GET_SIMPLE("NumbersWhite"));
    mEnergy =
      std::make_unique<Player::Indicator>(mVisibleUI, mPlayerEnergy, 16.0f, pRenderer, *GET_ANIMATED("Bolt"), *GET_SIMPLE("NumbersWhite"));

    // Binding player data
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::NORTH, *GET_ANIMATED("HumanIdleNorth"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::EAST, *GET_ANIMATED("HumanIdleEast"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, *GET_ANIMATED("HumanIdleSouth"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::WEST, *GET_ANIMATED("HumanIdleWest"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::NORTH, *GET_ANIMATED("HumanMovingNorth"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::EAST, *GET_ANIMATED("HumanMovingEast"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, *GET_ANIMATED("HumanMovingSouth"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::WEST, *GET_ANIMATED("HumanMovingWest"));

    mPlayer->setDirection(SOUTH);
    mPlayer->setAction(Objects::State::IDLE);

    pPlayerTexture  = mPlayer->getTexture();
    pPlayerView     = mPlayer->getTextureViewport();
    pPlayerPosition = mPlayer->getTexturePosition();
    mParticles      = std::make_shared<Objects::Particle>(*GET_SDL("FAE2C3"), 100, 0.5f, 0.5f);
    // Update all graphics
    mInterrupts[10]->addFunction([&]() { mGraphics->updateAnimatedTexture(); });

    mInterrupts[10]->addFunction([&]() {
        // Increment layers for top and bottom graphic
        mSegments.CurrentLayerBottom++;
        mSegments.CurrentLayerTop++;
        if (mSegments.CurrentLayerBottom >= mSegments.MaxLayerBottom) {
            mSegments.CurrentLayerBottom = 0;
        }
        if (mSegments.CurrentLayerTop >= mSegments.MaxLayerTop) {
            mSegments.CurrentLayerTop = 0;
        }
    });

    Common::addEventWatcher([&](SDL_Event* evt) { return mActionManager->eventHandler(evt); }, mEventWatcher);

    // Adding a slime
    mMonsters[Monster::SLIME] = new Monster::Slime(50, 0.5f, pPlayerPosition);
    mMonsters[Monster::SLIME]->addAnimatedTexture(Objects::IDLE, Directions::ALL, *GET_ANIMATED("SlimeIdle"));
    mMonsters[Monster::SLIME]->addAnimatedTexture(Objects::MOVE, Directions::ALL, *GET_ANIMATED("SlimeMoving"));
    mMonsters[Monster::SLIME]->addAnimatedTexture(Objects::DYING, Directions::ALL, *GET_ANIMATED("SlimeDead"));

    // Setup perspective
    mPerspective = std::make_unique<Common::Perspective>(pRenderer, offset.X, offset.Y, mPlayer->getPlayerCenter());
}

void
Engine::terminate() {
    mRun = false;
}

void
Engine::click() {
    const auto calculatedX = mActionManager->mouseX + (mPerspective->mOffset.x / -1.0f);
    const auto calculatedY = mActionManager->mouseY + (mPerspective->mOffset.y / -1.0f);
    auto       player      = Utility::getFRectCenter(*pPlayerPosition);
    auto       angle       = Utility::calculateAngle(player.first, player.second, calculatedX, calculatedY);
    mPlayerEnergy -= 3;

    Objects::typeProjectileStruct setup{ *GET_ANIMATED("Fireball"), *GET_SDL("RedCircle"), angle, 100, 5.0 };

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
    textBox = new Objects::TextBox(mGraphics->generateText("Hello ssss", 8), 20, 20);
    mPlayer->spawn(44, 120);
    mPerspective->center(pPlayerPosition->x + 8.0f, pPlayerPosition->y + 8.0f);

    // mLoading.join();

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
        mPerspective->render(*pPlayerTexture, *pPlayerView, pPlayerPosition); // Draw our cute hero
#ifdef DEBUG_MODE
        // Display interaction area
        mPerspective->render(*GET_SDL("0000FF"), nullptr, mPlayer->getInteractionArea());
        // Display player center
        SDL_FRect middle{ mPlayer->getPlayerCenter().x, mPlayer->getPlayerCenter().y, 1.0f, 1.0f };
        mPerspective->render(*GET_SDL("A349A4"), nullptr, &middle);
#endif
        monsters();
        projectiles();
        drawProjectiles();
        drawLevel(mSegments.Top, mSegments.CurrentLayerTop);
        addDarkness();
        drawNumbers();
        mHealth->draw();
        mEnergy->draw();

        present();

        auto ticks = mFPSTimer.getTicks();
        if (ticks < 1000.0 / 60.0)
            SDL_Delay((1000 / 60.0) - ticks);
    }
    delete textBox;
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
                mNumbers.push_back(
                  Graphics::Number({ (*it2)->getPosition()->x, (*it2)->getPosition()->y }, damage, 100, *GET_SIMPLE("NumbersWhite"), 0.5f));
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
Engine::drawLevel(std::vector<typeSegmentData>& data, const int& currentLayer) {
    for (auto& segment : data) {
        mPerspective->render(segment.Layers[currentLayer], nullptr, &segment.Position);
    }
    /*
    for (auto& door : doors) {
        auto drawData = door->getDrawData();
        mPerspective->render(drawData.Texture, drawData.Viewport, drawData.Position);
    }
     */
}

void
Engine::addDarkness() {
    auto t = GET_SDL("Shadow");
    if(t == nullptr)
        return;
    auto t1 = *t;
    SDL_RenderCopy(pRenderer, t1, nullptr, nullptr);
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
