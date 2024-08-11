#include <graphics/types/lightningTexture.hpp>

namespace Graphics {

LightningTexture::LightningTexture(SDL_Texture* texture, const int& w, const int& h, const int& ticks, const bool& paused)
  : mView(0)
  , mCycles(0)
  , mCurrentTicks(0)
  , mTicks(ticks)
  , mPaused(paused)
  , BaseTexture(texture, w, h, TextureTypes::LightningTexture) {}

LightningTexture::~LightningTexture() {}

SDL_Rect*
LightningTexture::getAnimatedViewport() {
    return &mCurrentViewport;
}

void
LightningTexture::addViewportDone() {
    mCurrentViewport = mViewports.front();
}

void
LightningTexture::updateTexture() {
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
LightningTexture::runCycles(const int& cycles) {
    mCycles = cycles;
}

bool
LightningTexture::done() const {
    return mView == (mViewports.size() - 1) ? true : false;
}

int
LightningTexture::getTicks() const {
    return mTicks;
}

}