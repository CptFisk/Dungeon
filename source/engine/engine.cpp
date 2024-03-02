#include <SDL3_ttf/SDL_ttf.h>
#include <common/handlers.hpp>
#include <common/scale.hpp>
#include <engine/engine.hpp>
#include <iostream>
#include <utility/file.hpp>
#include <utility/textures.hpp>
#include <utility/trigonometry.hpp>
#define GET_ANIMATED(VAR) mGraphics->getTexture<Graphics::AnimatedTexture*>(VAR)

namespace Engine {

Engine::Engine()
  : mInitHandler(std::make_unique<Common::InitHandler>())
  , pWindow(nullptr)
  , pRenderer(nullptr)
  , pPlayerPosition(nullptr)
  , pPlayerTexture(nullptr)
  , pPlayerView(nullptr)
  , mScale{}
  , mRun(true)
  , mVisibleUI(true)
  , mPlayerHealth(100)
  , mPlayerEnergy(50)
  , mActionManager(std::make_unique<Common::ActionManager>()) {}

Engine::~Engine() {
    mInitHandler->shutdown();
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
    TTF_Quit();
    SDL_Quit();
}

Common::ActionManager&
Engine::getActionManager() {
    return *mActionManager;
}

[[maybe_unused]] std::list<std::function<bool(SDL_Event*)>>&
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
    mThreads.push_back(spawnInterrupt(300));
    mThreads.push_back(spawnInterrupt(500));
    mThreads.push_back(spawnInterrupt(1000));

    mInitHandler->addInitializer(std::make_shared<Common::SDLInitializer>(&pWindow, &pRenderer, "Veras adventure"));
    mInitHandler->startup();
    Common::calculateGameScale(mScale, pWindow);
    // Generate graphics
    mGraphics = std::make_shared<Graphics::Graphics>(pRenderer, mScale);
    mGraphics->init();

    mLevel = std::make_unique<Level::Level>(pRenderer, mScale, mGraphics);
    mLevel->loadLevel("level.map");
    mPlayer = std::make_unique<Player::Player>(mScale);

    mHealth = std::make_unique<Player::Indicator>(mVisibleUI,
                                                  mPlayerHealth,
                                                  32.0f,
                                                  pRenderer,
                                                  mScale,
                                                  GET_ANIMATED("Heart"),
                                                  mGraphics->getTexture<Graphics::typeSimpleTexture>("NumbersWhite"));
    mEnergy = std::make_unique<Player::Indicator>(mVisibleUI,
                                                  mPlayerEnergy,
                                                  16.0f,
                                                  pRenderer,
                                                  mScale,
                                                  GET_ANIMATED("Bolt"),
                                                  mGraphics->getTexture<Graphics::typeSimpleTexture>("NumbersWhite"));

    // Binding player data
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::NORTH, GET_ANIMATED("HumanIdleNorth"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::EAST, GET_ANIMATED("HumanIdleEast"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, GET_ANIMATED("HumanIdleSouth"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::WEST, GET_ANIMATED("HumanIdleWest"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::NORTH, GET_ANIMATED("HumanMovingNorth"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::EAST, GET_ANIMATED("HumanMovingEast"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, GET_ANIMATED("HumanMovingSouth"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::WEST, GET_ANIMATED("HumanMovingWest"));

    mPlayer->setDirection(SOUTH);
    mPlayer->setAction(Objects::State::IDLE);

    pPlayerTexture  = mPlayer->getPlayerTexture();
    pPlayerView     = mPlayer->getPlayerViewport();
    pPlayerPosition = mPlayer->getPlayerPosition();
    mParticles      = std::make_shared<Objects::Particle>(mGraphics->getTexture<SDL_Texture*>("FAE2C3"), pRenderer, 100, 3, 5);
    // Update all graphics
    mInterrupts[10]->addFunction([&]() { mGraphics->updateAnimatedTexture(); });

    Common::addEventWatcher([&](SDL_Event* evt) { return mActionManager->eventHandler(evt); }, mEventWatcher);

    // Adding a slime
    mMonsters[Monster::SLIME] = new Monster::Slime(50, 0.5f, pPlayerPosition);
    mMonsters[Monster::SLIME]->addAnimatedTexture(Objects::IDLE, Directions::ALL, GET_ANIMATED ("SlimeIdle"));
    mMonsters[Monster::SLIME]->addAnimatedTexture(Objects::MOVE, Directions::ALL, GET_ANIMATED ("SlimeMoving"));
    mMonsters[Monster::SLIME]->addAnimatedTexture(Objects::DYING, Directions::ALL, GET_ANIMATED("SlimeDead"));
    //mMonsters[Monster::SLIME]->addAnimatedTexture(Objects::DEAD, Directions::ALL, GET_ANIMATED("SlimeDead"));
}

void
Engine::terminate() {
    mRun = false;
}

void
Engine::click(const float& x, const float& y) {
    auto player = Utility::getFRectCenter(*pPlayerPosition);
    auto angle  = Utility::calculateAngle(player.first, player.second, x, y);
    mPlayerEnergy -= 3;

    Objects::typeProjectileStruct setup{
        mGraphics->getTexture<Graphics::AnimatedTexture*>("Fireball"), mGraphics->getTexture<SDL_Texture*>("RedCircle"), angle, 100, 5.0
    };

    mProjectiles.push_back(new Objects::Projectile(setup, { pPlayerPosition->x, pPlayerPosition->y }, mScale, pRenderer, mParticles));
}

void
Engine::movePlayer(Directions direction) {
    if (mLevel->movement(*pPlayerPosition, direction))
        mPlayer->move(direction);
}

void
Engine::setPlayerAction(Objects::State action) {
    mPlayer->setAction(action);
}

void
Engine::mainLoop() {
    // Spawn some slime
    mActiveMonsters.push_back(mMonsters[Monster::SLIME]->spawn(100, 100));
    mActiveMonsters.push_back(mMonsters[Monster::SLIME]->spawn(500, 500));
    mActiveMonsters.push_back(mMonsters[Monster::SLIME]->spawn(500, 50));

    auto number = mGraphics->getTexture<Graphics::typeSimpleTexture>("NumbersWhite");
    SDL_FRect pos = {50.0f,50.0f, 16.0f,16.0f};

    SDL_Event event;
    while (mRun) {
        mFPSTimer.start();

        SDL_RenderClear(pRenderer);
        while (SDL_PollEvent(&event)) {
            bool accepted = true;

            for (auto& handler : mEventWatcher) {
                if (!handler(&event)) {
                    accepted = false;
                    break;
                }
            }

            if (accepted && mEvents.find(event.type) != mEvents.end()) {
                auto handlers = mEvents[event.type];
                for (auto& handler : handlers) {
                    if (!handler(&event))
                        break;
                }
            }
        }

        for (auto& [handler, timer] : mProcessing) {
            handler(timer.getTicks());
            timer.start();
        }
        mLevel->draw();
        SDL_RenderTexture(pRenderer, *pPlayerTexture, *pPlayerView, pPlayerPosition);
        projectiles();
        drawParticles();
        monsters();
        addDarkness();
        // Draw UI-elements
        mHealth->draw();
        mEnergy->draw();
        SDL_RenderTexture(pRenderer, number.Texture, &number.Views[0], &pos);
        present();

        auto ticks = mFPSTimer.getTicks();
        if (ticks < 1000.0 / 60)
            SDL_Delay((1000 / 60) - ticks);
    }
}

void
Engine::projectiles() {
    for (auto it = mProjectiles.begin(); it != mProjectiles.end();) {
        bool removed = false;
        // Check monster for collision
        for (auto it2 = mActiveMonsters.begin(); it2 != mActiveMonsters.end();) {
            if (Utility::isOverlapping(*(*it)->getPosition(), *(*it2)->getPosition())) {
                delete *it;                  // Free memory
                it = mProjectiles.erase(it); // Move iterator
                (*it2)->damageMonster(30);

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
                (*it)->draw();
                ++it;
            }
        }
    }
}

void
Engine::monsters() {
    for(auto it = mActiveMonsters.begin(); it != mActiveMonsters.end();){
        if((*it)->getState() == Objects::DEAD){
            it = mActiveMonsters.erase(it);
        }else{
            const auto data = (*it)->getMonster();
            SDL_RenderTexture(pRenderer, data.Texture, data.Viewport, data.Position);
            ++it;
        }
    }
}

void
Engine::drawParticles() {
    mParticles->draw();
}

void
Engine::addDarkness() {
    SDL_RenderTexture(pRenderer, mGraphics->getTexture<SDL_Texture*>("Shadow"), nullptr, nullptr);
}

std::thread
Engine::spawnInterrupt(const long& time) {
    auto thread = std::thread([&]() {
        auto interrupt    = std::make_shared<Interrupt>(time, mRun);
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
