#include <graphics/types/animatedTexture.hpp>

namespace Graphics {

AnimatedTexture::AnimatedTexture(SDL_Texture* texture, const int& w, const int& h, const int& ticks, const bool& paused)
  : mView(0)
  , mCycles(0)
  , mCurrentTicks(0)
  , mTicks(ticks)
  , mPaused(paused)
  , BaseTexture(texture, w, h, TextureTypes::AnimatedTexture) {}

AnimatedTexture::~AnimatedTexture() {}

SDL_Rect*
AnimatedTexture::getAnimatedViewport() {
    return &mCurrentViewport;
}

void
AnimatedTexture::addViewportDone() {
    mCurrentViewport = mViewports.front();
}

void
AnimatedTexture::updateTexture() {
    if (mCurrentTicks > mTicks && (mPaused == false || (mPaused == true && mCycles > 0))) {
        if (mView < (mViewports.size() - 1)) {
            mView++;
        } else {
            mView   = 0;
            mCycles = std::max(0, mCycles - 1);
        }
        mCurrentViewport = mViewports[mView];
        mCurrentTicks    = 0;
    } else {
        mCurrentTicks++;
    }
}

void
AnimatedTexture::runCycles(const int& cycles) {
    mCycles = cycles;
}

bool
AnimatedTexture::done() const {
    return mView == (mViewports.size() - 1) ? true : false;
}

int
AnimatedTexture::getTicks() const {
    return mTicks;
}

}