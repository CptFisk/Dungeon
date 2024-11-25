#include <global.hpp>
#include <iostream>
#include <object/door.hpp>
namespace Objects {

Door::Door(const int& x, const int& y, Graphics::AnimatedTexture* opening, Graphics::AnimatedTexture* closing, bool open)
  : mOpen(open)
  , mAnimationOpening(opening)
  , mAnimationOpeningViewport(opening->getViewports())
  , mAnimationClosing(closing)
  , mAnimationClosingViewport(closing->getViewports()) {
    /*
     * To calculate the door position we use x and y. And then offset with the size of the graphics.
     * For this to work, we need the animations to have the same size
     */
    if (opening->getWidth() != closing->getWidth() || opening->getHeight() != closing->getHeight()) {
        std::cerr << "The animations need to have the same size" << std::endl;
        return;
    }
    mPosition          = SDL_FRect{ (FLOAT(x) * 16.0f) + FLOAT(16 - opening->getWidth()),
                           (FLOAT(y) * 16.0f) + FLOAT(16 - opening->getHeight()),
                           opening->getWidthF(),
                           opening->getHeightF() };
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
                for (auto& viewport : mAnimationClosingViewport) {
                    mDrawData.Viewport = &viewport;
                    std::this_thread::sleep_for(std::chrono::milliseconds(10 * 6));
                }
                mDrawData.Texture  = mAnimationOpening->getTexture();
                mDrawData.Viewport = &mAnimationOpeningViewport.front();
            });
        } else {
            if (mThread.joinable())
                mThread.join();

            mThread = std::thread([&]() {
                for (auto& viewport : mAnimationOpeningViewport) {
                    mDrawData.Viewport = &viewport;
                    std::this_thread::sleep_for(std::chrono::milliseconds(10 * 6));
                }
                mDrawData.Texture  = mAnimationClosing->getTexture();
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

Graphics::typeDrawData&
Door::getDrawData() {
    return mDrawData;
}

}