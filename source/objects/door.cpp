#include <iostream>
#include <objects/door.hpp>

namespace Objects {

Door::Door(const SDL_FRect& position, Graphics::AnimatedTexture* opening, Graphics::AnimatedTexture* closing, bool open)
  : mPosition(position)
  , mOpen(open)
  , mAnimationOpening(opening)
  , mAnimationOpeningViewport(opening->getViewports())
  , mAnimationClosing(closing)
  , mAnimationClosingViewport(closing->getViewports()) {
    mDrawData.Position = &mPosition;
    if (open) {
        mDrawData.Viewport = &mAnimationClosingViewport.front();
        mDrawData.Texture  = closing->getTexture();
    } else {
        mDrawData.Viewport = &mAnimationOpeningViewport.front();
        mDrawData.Texture  = opening->getTexture();
    }
}

Door::~Door() {
    if (mThread.joinable())
        mThread.join();
}

void
Door::interact(bool condition) {
    bool prevState = mOpen;
    mOpen          = !mOpen && condition;
    if (prevState != mOpen) {
        // Detect change in door
        if (prevState) {
            if (mThread.joinable())
                mThread.join();

            mThread = std::thread([&]() {
                for(auto& viewport : mAnimationClosingViewport){
                    mDrawData.Viewport = &viewport;
                    std::this_thread::sleep_for(std::chrono::milliseconds (10 * 6));
                }
                mDrawData.Viewport = &mAnimationOpeningViewport.front();
            });
        } else {
            if (mThread.joinable())
                mThread.join();

            mThread = std::thread([&]() {
                for(auto& viewport : mAnimationOpeningViewport){
                    mDrawData.Viewport = &viewport;
                    std::this_thread::sleep_for(std::chrono::milliseconds (10 * 6));
                }
                mDrawData.Viewport = &mAnimationClosingViewport.front();
            });
        }
    }
}

bool
Door::isPassable() const {
    return mOpen == true ? true : false;
}

SDL_FRect
Door::getPosition() const {
    return mPosition;
}

Common::typeDrawData&
Door::getDrawData() {
    return mDrawData;
}

}