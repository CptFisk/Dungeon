#include <graphics/animatedTexture.hpp>

namespace Graphics {
AnimatedTexture::AnimatedTexture()
  : mView(0)
  , mTicks(0)
  , mCurrentTicks(0)
  , mCycles(0)
  , Width(0)
  , Height(0)
  , mCurrentViewport{}
  , mTexture(nullptr)
  , mPaused(false) {}

AnimatedTexture::AnimatedTexture(SDL_Texture* texture, const int& w, const int& h, const int& ticks, const bool& paused)
  : mView(0)
  , mCycles(0)
  , mCurrentTicks(0)
  , mTexture(texture)
  , mCurrentViewport{}
  , Width(w)
  , Height(h)
  , mTicks(ticks)
  , mPaused(paused) {}

AnimatedTexture::~AnimatedTexture() {
    SDL_DestroyTexture(mTexture); // Cleaning
}

SDL_Texture*&
AnimatedTexture::getTexture() {
    return mTexture;
}

SDL_Rect*
AnimatedTexture::getViewport() {
    return &mCurrentViewport;
}

SDL_Rect*
AnimatedTexture::getViewport(const int& pos) {
    return &mViewports[pos];
}

void
AnimatedTexture::addViewport(const SDL_Rect& view) {
    mViewports.push_back(view);
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

std::vector<SDL_Rect>
AnimatedTexture::getViewports() {
    return mViewports;
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