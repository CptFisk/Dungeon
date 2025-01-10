#include <common/initializer/initializer.hpp>
#include <common/initializer/sdl.hpp>
#include <common/initializer/sdlTTF.hpp>
#include <engine/engine.hpp>
namespace Engine {
void
Engine::startup() {
    // Starting interrupts
    mThreads.push_back(spawnInterrupt(10));
    mThreads.push_back(spawnInterrupt(100));
    mThreads.push_back(spawnInterrupt(500));

    Common::calculateGameScale(mScale, pWindow);
    SDL_RenderSetScale(pRenderer, static_cast<int>(mScale.selectedScale), static_cast<int>(mScale.selectedScale));

    // Generate all monster data
    createMonsters();
    createNPC();

    loadLevel("555.lvl");
    SDL_RenderClear(pRenderer);

    mTextbox = std::make_unique<UI::Textbox>(pRenderer, mScale);
    // Textbox
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

    // Binding player data
    mPlayerStats =
      std::make_unique<Player::PlayerStats>(mInventory->getItemStats(), pRenderer, GET_USERINTERFACE("Stats"), GET_TTF(DEFAULT_FONT));

    mPlayer->addAnimatedTexture(Objects::IDLE, Orientation::North, GET_ANIMATED("HumanIdleNorth"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Orientation::East, GET_ANIMATED("HumanIdleEast"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Orientation::South, GET_ANIMATED("HumanIdleSouth"));
    mPlayer->addAnimatedTexture(Objects::IDLE, Orientation::West, GET_ANIMATED("HumanIdleWest"));

    mPlayer->addAnimatedTexture(Objects::MOVE, Orientation::North, GET_ANIMATED("HumanMovingNorth"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Orientation::East, GET_ANIMATED("HumanMovingEast"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Orientation::South, GET_ANIMATED("HumanMovingSouth"));
    mPlayer->addAnimatedTexture(Objects::MOVE, Orientation::West, GET_ANIMATED("HumanMovingWest"));

    mPlayer->addAnimatedTexture(Objects::DEAD, Orientation::North, GET_ANIMATED("HumanDead"));
    mPlayer->addAnimatedTexture(Objects::DEAD, Orientation::East, GET_ANIMATED("HumanDead"));
    mPlayer->addAnimatedTexture(Objects::DEAD, Orientation::South, GET_ANIMATED("HumanDead"));
    mPlayer->addAnimatedTexture(Objects::DEAD, Orientation::West, GET_ANIMATED("HumanDead"));

    mPlayer->addSweepTexture(Orientation::North, GET_ANIMATED("AttackSweepNorth"));
    mPlayer->addSweepTexture(Orientation::South, GET_ANIMATED("AttackSweepSouth"));
    mPlayer->addSweepTexture(Orientation::East, GET_ANIMATED("AttackSweepEast"));
    mPlayer->addSweepTexture(Orientation::West, GET_ANIMATED("AttackSweepWest"));

    mPlayer->setDirection(South);
    mPlayer->setAction(Objects::State::IDLE);

    pPlayerTexture  = mPlayer->getTexture();
    pPlayerView     = mPlayer->getTextureViewport();
    pPlayerPosition = mPlayer->getTexturePosition();
    pPlayerAction   = mPlayer->getAction();

    // Setting up inventory
    mInventory = std::make_unique<Items::Inventory>();
    createItems();

    mUserInterface = std::make_unique<UI::UserInterface>(mGraphics,
                                                         pRenderer,
                                                         mScale,
                                                         mInventory->getSlots(),
                                                         mPlayerStats->getTotalStats(),
                                                         mInventory->getItemStats());

    mParticles = std::make_shared<Objects::Particle>(GET_GENERATED("FAE2C3")->getTexture(), 100, 0.5f, 0.5f);
    // mInterrupts[0]->addFunction([&]() { monsterActions(); });
    //  Update all graphics
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