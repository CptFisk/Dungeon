#include <SDL_image.h>
#include <engine/engine.hpp>
#include <utility/file.hpp>

namespace Engine {

Engine::Engine()
  : mInitHandler(std::make_unique<InitHandler>())
  , pWindow(nullptr)
  , pRenderer(nullptr)
  , pPlayerPosition(nullptr)
  , pPlayerTexture(nullptr)
  , pPlayerView(nullptr)
  , mScaleX(0.0f)
  , mScaleY(0.0f)
  , mRun(true)
  , mActionManager(std::make_unique<ActionManager>()) {}

Engine::~Engine() {
    mInitHandler->shutdown();

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
    mThreads.push_back(spawnInterrupt(100));
    mThreads.push_back(spawnInterrupt(300));
    mThreads.push_back(spawnInterrupt(500));
    mThreads.push_back(spawnInterrupt(1000));

    mInitHandler->addInitializer(std::make_shared<SDLInitializer>(&pWindow, &pRenderer));
    mInitHandler->startup();
    calculateScale();
    // Generate graphics
    mGraphics = std::make_shared<Graphics::Graphics>(pRenderer, mScaleX, mScaleY);
    mLevel    = std::make_shared<Level>(pRenderer);
    mPlayer   = std::make_unique<Player::Player>(mScaleX, mScaleY);

    mLevel->generateLevel(mGraphics->getBaseTexture("PurpleFloor"));

    mGraphics->generateCircle("Circle", 16, 247, 111, 29, 64);
    mGraphics->generateSquare("Darkness", 1, 1, 0, 0, 0, 128);

    // Binding player data
    mPlayer->addAnimatedTexture(Objects::Idle, Directions::North, mGraphics->getAnimatedTexture("HumanIdleNorth"));
    mPlayer->addAnimatedTexture(Objects::Idle, Directions::East, mGraphics->getAnimatedTexture("HumanIdleEast"));
    mPlayer->addAnimatedTexture(Objects::Idle, Directions::South, mGraphics->getAnimatedTexture("HumanIdleSouth"));
    mPlayer->addAnimatedTexture(Objects::Idle, Directions::West, mGraphics->getAnimatedTexture("HumanIdleWest"));
    mPlayer->addAnimatedTexture(Objects::Moving, Directions::North, mGraphics->getAnimatedTexture("HumanMovingNorth"));
    mPlayer->addAnimatedTexture(Objects::Moving, Directions::East, mGraphics->getAnimatedTexture("HumanMovingEast"));
    mPlayer->addAnimatedTexture(Objects::Moving, Directions::South, mGraphics->getAnimatedTexture("HumanMovingSouth"));
    mPlayer->addAnimatedTexture(Objects::Moving, Directions::West, mGraphics->getAnimatedTexture("HumanMovingWest"));

    mPlayer->setDirection(South);
    mPlayer->setAction(Objects::ObjectAction::Idle);

    pPlayerTexture  = mPlayer->getPlayerTexture();
    pPlayerView     = mPlayer->getPlayerViewport();
    pPlayerPosition = mPlayer->getPlayerPosition();
    // Bind animation for player to
    mInterrupts[300]->addFunction([&]() { mPlayer->updateAnimation(); });

    addEventWatcher([&](SDL_Event* evt) { return mActionManager->eventHandler(evt); });
}

void
Engine::terminate() {
    mRun = false;
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
    SDL_FRect lightPos = {10,10,100,100};
    SDL_Event event;
    while (mRun) {
        SDL_RenderClear(pRenderer);
        while(SDL_PollEvent(&event)){
            bool accepted = true;

            for(auto &handler : mEventWatcher){
                if(!handler(&event)){
                    accepted = false;
                    break;
                }
            }

            if(accepted && mEvents.find(event.type) != mEvents.end()){
                auto handlers = mEvents[event.type];
                for(auto &handler : handlers){
                    if(!handler(&event))
                        break;
                }
            }
        }

        for(auto& [handler, timer] : mProcessing){
            handler(timer.getTicks());
            timer.start();
        }

        mLevel->drawLevel();

        SDL_RenderTexture(pRenderer, *pPlayerTexture, *pPlayerView, pPlayerPosition);
        addDarkness();
        SDL_RenderTexture(pRenderer, mGraphics->getTexture("Circle"), nullptr, &lightPos);
        present();
    }
}

void
Engine::addDarkness() {
    SDL_RenderTexture(pRenderer, mGraphics->getTexture("Darkness"), nullptr, nullptr);
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
    // The goal is to have 16 by 12 squares
    mScaleX = static_cast<float>(width) / 16.0f;
    mScaleY = static_cast<float>(height) / 12.0f;
}

}
