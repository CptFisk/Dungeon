#include <SDL_image.h>
#include <engine/engine.hpp>
#include <iostream>
#include <utility/file.hpp>
#include <utility/trigonometry.hpp>

namespace Engine {

Engine::Engine()
  : mInitHandler(std::make_unique<InitHandler>())
  , pWindow(nullptr)
  , pRenderer(nullptr)
  , pPlayerPosition(nullptr)
  , pPlayerTexture(nullptr)
  , pPlayerView(nullptr)
  , mScale{}
  , mRun(true)
  , mActionManager(std::make_unique<ActionManager>()) {}

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
    SDL_Quit();
}

ActionManager&
Engine::getActionManager() {
    return *mActionManager;
}

void
Engine::startup() {
    // Starting interrupts
    mThreads.push_back(spawnInterrupt(10));
    mThreads.push_back(spawnInterrupt(300));
    mThreads.push_back(spawnInterrupt(500));
    mThreads.push_back(spawnInterrupt(1000));

    mInitHandler->addInitializer(std::make_shared<SDLInitializer>(&pWindow, &pRenderer));
    mInitHandler->startup();
    calculateScale();
    // Generate graphics
    mGraphics = std::make_shared<Graphics::Graphics>(pRenderer, mScale);
    mGraphics->init();
    mLevel  = std::make_shared<Level>(pRenderer);
    mPlayer = std::make_unique<Player::Player>(mScale);

    mLevel->generateLevel(mGraphics->getBaseTexture("PurpleFloor"));

    // Binding player data
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::North, mGraphics->getAnimatedTexture("HumanIdleNorth"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::East, mGraphics->getAnimatedTexture("HumanIdleEast"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::South, mGraphics->getAnimatedTexture("HumanIdleSouth"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Directions::West, mGraphics->getAnimatedTexture("HumanIdleWest"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::North, mGraphics->getAnimatedTexture("HumanMovingNorth"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::East, mGraphics->getAnimatedTexture("HumanMovingEast"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::South, mGraphics->getAnimatedTexture("HumanMovingSouth"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Directions::West, mGraphics->getAnimatedTexture("HumanMovingWest"));

    mPlayer->setDirection(South);
    mPlayer->setAction(Objects::ObjectAction::IDLE);

    pPlayerTexture  = mPlayer->getPlayerTexture();
    pPlayerView     = mPlayer->getPlayerViewport();
    pPlayerPosition = mPlayer->getPlayerPosition();
    // Bind animation for player to
    mInterrupts[10]->addFunction([&]() { mGraphics->updateAnimatedTexture(); });

    addEventWatcher([&](SDL_Event* evt) { return mActionManager->eventHandler(evt); });
}

void
Engine::terminate() {
    mRun = false;
}

void
Engine::click(const float& x, const float& y) {
    std::pair<float, float> player(pPlayerPosition->x, pPlayerPosition->y);
    std::pair<float, float> mouse(x, y);

    auto angle = Utility::calculateAngle(player, mouse);

    Objects::ProjectileStruct setup{
        mGraphics->getAnimatedTexture("Fireball"), mGraphics->getTexture("RedCircle"), angle, 100, 5.0
    };

    mProjectiles.push_back(new Objects::Projectile(setup, pRenderer));
}

void
Engine::movePlayer(Directions direction) {
    mPlayer->move(direction);
}

void
Engine::setPlayerAction(Objects::ObjectAction action) {
    mPlayer->setAction(action);
}

void
Engine::mainLoop() {

    Objects::ProjectileStruct setup{
        mGraphics->getAnimatedTexture("Fireball"), mGraphics->getTexture("RedCircle"), 0, 100, 5
    };
    mProjectiles.push_back(new Objects::Projectile(setup, pRenderer));

    SDL_FRect lightPos = { 10, 10, 100, 100 };
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

        mLevel->drawLevel();

        SDL_RenderTexture(pRenderer, *pPlayerTexture, *pPlayerView, pPlayerPosition);
        addDarkness();
        projectiles();
        present();

        auto ticks = mFPSTimer.getTicks();
        if (ticks < 1000.0 / 60)
            SDL_Delay((1000.0 / 60) - ticks);
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
Engine::addDarkness() {
    if (SDL_RenderTexture(pRenderer, mGraphics->getTexture("Shadow"), nullptr, nullptr) != 0)
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

void
Engine::calculateScale() {
    int width, height;
    SDL_GetWindowSizeInPixels(pWindow, &width, &height);
    const float squaresX  = 16.0; // Numbers of square in x-direction
    const float squareY   = 12.0; // Numbers of square in y-direction
    const float pixelSize = 16.0;
    mScale.ScaleX         = (static_cast<float>(width) / squaresX) / pixelSize;
    mScale.ScaleY         = (static_cast<float>(height) / squareY) / pixelSize;
}

}
