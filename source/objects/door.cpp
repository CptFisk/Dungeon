#include <objects/door.hpp>

namespace Objects {

Door::Door(const SDL_FRect& position, Graphics::AnimatedTexture* opening, Graphics::AnimatedTexture* closing, bool open)
  : mPosition(position)
  , mOpen(open)
  , mAnimationOpening(opening)
  , mAnimationClosing(closing) {
    mDrawData.Position = &mPosition;
    if (open) {
        mDrawData.Viewport = closing->getViewport();
        mDrawData.Texture  = closing->getTexture();
    } else {
        mDrawData.Viewport = opening->getViewport();
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
        if (mOpen) {
            mAnimationOpening->runCycles(1);
            if (mThread.joinable())
                mThread.join();
            mThread = std::thread([&]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(mAnimationOpening->getTicks() * 10));
                setOpenGraphic();
            });
        } else {
            mAnimationClosing->runCycles(1);
            if (mThread.joinable())
                mThread.join();

            mThread = std::thread([&]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(mAnimationClosing->getTicks() * 10));
                setClosedGraphic();
            });
        }
    }
}

void
Door::setOpenGraphic() {
    std::lock_guard<std::mutex> guard(mtx);
    mDrawData.Texture  = mAnimationClosing->getTexture();
    mDrawData.Viewport = mAnimationClosing->getViewport();
}

void
Door::setClosedGraphic() {
    std::lock_guard<std::mutex> guard(mtx);
    mDrawData.Texture  = mAnimationOpening->getTexture();
    mDrawData.Viewport = mAnimationOpening->getViewport();
}

Common::typeDrawData&
Door::getDrawData() {
    std::lock_guard<std::mutex> guard(mtx);
    return mDrawData;
}

std::thread&
Door::getThread() {
    return mThread;
}

}