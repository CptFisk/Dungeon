#include <SDL3_ttf/SDL_ttf.h>
#include <common/handlers.hpp>
#include <common/scale.hpp>
#include <engine/engine.hpp>
#include <iostream>
#include <utility/file.hpp>
#include <utility/textures.hpp>
#include <utility/trigonometry.hpp>

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
  , mActionManager(std::make_unique<Common::ActionManager>()) {}

Engine::~Engine() {
    mInitHandler->shutdown();
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
                                               pRenderer,
                                               mScale,
                                               mGraphics->getTexture<Graphics::AnimatedTexture*>("Bolt"),
                                               mGraphics->getTexture<Graphics::typeSimpleTexture>("NumbersWhite"));

    // Binding player data
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::North, mGraphics->getTexture<Graphics::AnimatedTexture*>("HumanIdleNorth"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::East, mGraphics->getTexture<Graphics::AnimatedTexture*>("HumanIdleEast"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::South, mGraphics->getTexture<Graphics::AnimatedTexture*>("HumanIdleSouth"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::West, mGraphics->getTexture<Graphics::AnimatedTexture*>("HumanIdleWest"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::North, mGraphics->getTexture<Graphics::AnimatedTexture*>("HumanMovingNorth"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::East, mGraphics->getTexture<Graphics::AnimatedTexture*>("HumanMovingEast"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::South, mGraphics->getTexture<Graphics::AnimatedTexture*>("HumanMovingSouth"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::West, mGraphics->getTexture<Graphics::AnimatedTexture*>("HumanMovingWest"));

    mPlayer->setDirection(South);
    mPlayer->setAction(Objects::ObjectAction::IDLE);

    pPlayerTexture  = mPlayer->getPlayerTexture();
    pPlayerView     = mPlayer->getPlayerViewport();
    pPlayerPosition = mPlayer->getPlayerPosition();
    mParticles      = std::make_shared<Objects::Particle>(mGraphics->getTexture<SDL_Texture*>("FAE2C3"), pRenderer, 100, 3, 5);
    // Update all graphics
    mInterrupts[10]->addFunction([&]() { mGraphics->updateAnimatedTexture(); });

    Common::addEventWatcher([&](SDL_Event* evt) { return mActionManager->eventHandler(evt); }, mEventWatcher);

    SDL_SetRenderDrawColor(pRenderer, 0, 0, 24, SDL_ALPHA_OPAQUE);
}

void
Engine::terminate() {
    mRun = false;
}

void
Engine::click(const float& x, const float& y) {
    std::pair<float, float> player(pPlayerPosition->x, pPlayerPosition->y);
    auto                    angle = Utility::calculateAngle(pPlayerPosition->x, pPlayerPosition->y, x, y);

    Objects::ProjectileStruct setup{
        mGraphics->getTexture<Graphics::AnimatedTexture*>("Fireball"), mGraphics->getTexture<SDL_Texture*>("RedCircle"), angle, 100, 5.0
    };

    mProjectiles.push_back(new Objects::Projectile(setup, player, mScale, pRenderer, mParticles));
}

void
Engine::movePlayer(Directions direction) {
    if (mLevel->movement(*pPlayerPosition, direction))
        mPlayer->move(direction);
}

void
Engine::setPlayerAction(Objects::ObjectAction action) {
    mPlayer->setAction(action);
}

void
Engine::mainLoop() {

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
        particles();
        addDarkness();
        mHealth->draw();

        present();

        auto ticks = mFPSTimer.getTicks();
        if (ticks < 1000.0 / 60)
            SDL_Delay((1000 / 60) - ticks);
    }
}

void
Engine::projectiles() {
    for (auto it = mProjectiles.begin(); it != mProjectiles.end();) {
        if ((*it)->getNewDuration() < 0) {
            delete *it;
            it = mProjectiles.erase(it);
        } else {
            (*it)->draw();
            ++it;
        }
    }
}

void
Engine::particles() {
    mParticles->draw();
}

void
Engine::addDarkness() {
    if (SDL_RenderTexture(pRenderer, mGraphics->getTexture<SDL_Texture*>("Shadow"), nullptr, nullptr) != 0)
        std::cout << SDL_GetError() << std::endl;
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
