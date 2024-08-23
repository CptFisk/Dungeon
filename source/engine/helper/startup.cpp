#include <engine/engine.hpp>

namespace Engine {
void
Engine::startup() {
    // Starting interrupts
    mThreads.push_back(spawnInterrupt(10));
    mThreads.push_back(spawnInterrupt(100));
    mThreads.push_back(spawnInterrupt(500));
    // 1280 960
    mInitHandler.addInitializer(std::make_shared<Common::SDLInitializer>(pWindow, pRenderer, 1920, 1080, false, "Vera adventure"));
    mInitHandler.startup();
    // 1920 1080

    Common::calculateGameScale(mScale, pWindow);
    SDL_RenderSetScale(pRenderer, mScale.selectedScale, mScale.selectedScale);
    mActionManager = std::make_unique<Common::ActionManager>(pRenderer, mScale);

    // Generate graphics
    mGraphics = std::make_shared<Graphics::Graphics>(pRenderer);
    mGraphics->init();

    mPlayer = std::make_unique<Player::Player>();
    // Generate all monster data
    createMonsters();
    loadLevel("554.map");
    SDL_RenderClear(pRenderer);


    mTextbox = std::make_unique<UI::Textbox>(pRenderer, mScale);
    //Textbox
    mTextbox->addElements(UI::TextboxSize::Small,
                          GET_USERINTERFACE("TextboxSmallStart"),
                          GET_USERINTERFACE("TextboxSmallCenter"),
                          GET_USERINTERFACE("TextboxSmallEnd"));
    mTextbox->addElements(UI::TextboxSize::Medium,
                          GET_USERINTERFACE("TextboxMediumStart"),
                          GET_USERINTERFACE("TextboxMediumCenter"),
                          GET_USERINTERFACE("TextboxMediumEnd"));
    mTextbox->addElements(UI::TextboxSize::Large,
                          GET_USERINTERFACE("TextboxLargeStart"),
                          GET_USERINTERFACE("TextboxLargeCenter"),
                          GET_USERINTERFACE("TextboxLargeEnd"));
    mTextbox->generateBoxes();

    mHealth = std::make_unique<Player::Indicator>(mPlayerHealth, mScale, GET_USERINTERFACE("HealthBase"), GET_USERINTERFACE("HealthRed"));
    /*
  mEnergy =
    std::make_unique<Player::Indicator>(mVisibleUI, mPlayerEnergy, 16.0f, pRenderer, GET_ANIMATED("Bolt"), GET_NUMBER("NumberWhite"));
  */
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

    pPlayerTexture  = mPlayer->getTexture();
    pPlayerView     = mPlayer->getTextureViewport();
    pPlayerPosition = mPlayer->getTexturePosition();

    mParticles = std::make_shared<Objects::Particle>(GET_GENERATED("FAE2C3")->getTexture(), 100, 0.5f, 0.5f);
    // Update all graphics
    mInterrupts[10]->addFunction([&]() { mGraphics->updateAnimatedTexture(); });
    mInterrupts[10]->addFunction([&]() {
        {
            std::lock_guard<std::mutex> lock(mMutex);
            // Increment layers for top and bottom graphic
            mSegments.CurrentLayerBottom++;
            mSegments.CurrentLayerTop++;

            if (mSegments.CurrentLayerBottom >= mSegments.MaxLayerBottom)
                mSegments.CurrentLayerBottom = 0;
            if (mSegments.CurrentLayerTop >= mSegments.MaxLayerTop)
                mSegments.CurrentLayerTop = 0;
        }
    });
    mInterrupts[100]->addFunction([&]() {
        {
            std::lock_guard<std::mutex> lock(mMutex);
            mSegments.CurrentLayerLightning++;
            if (mSegments.CurrentLayerLightning >= mSegments.MaxLayerLightning)
                mSegments.CurrentLayerLightning = 0;
        }
    });

    Common::addEventWatcher([&](SDL_Event* evt) { return mActionManager->eventHandler(evt); }, mEventWatcher);
    // Setup perspective
    mPerspective = std::make_unique<Common::Perspective>(pRenderer, offset.X, offset.Y, mPlayer->getPlayerCenter(), mScale);
}
}