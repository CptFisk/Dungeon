#include <graphics/animatedTexture.hpp>

namespace Graphics {
AnimatedTexture::AnimatedTexture()
  : mView(0)
  , mTicks(0)
  , mCurrentTicks(0)
  , mCurrentViewport{}
  , mTexture(nullptr) {}

AnimatedTexture::AnimatedTexture(SDL_Texture* texture, const int& ticks)
  : mTexture(texture)
  , mView(0)
  , mCurrentTicks(0)
  , mCurrentViewport{}
  , mTicks(ticks) {}

AnimatedTexture::~AnimatedTexture() {
    SDL_DestroyTexture(mTexture); // Cleaning
}

SDL_Texture*&
AnimatedTexture::getTexture(){
    return mTexture;
}

SDL_Rect*
AnimatedTexture::getViewport() {
    return &mCurrentViewport;
}

void
AnimatedTexture::addViewport(const SDL_Rect& view) {
    mViewports.push_back(view);
    mCurrentViewport = mViewports.front();
}

void
AnimatedTexture::updateTexture() {
    if (mCurrentTicks > mTicks) {
        if (mView < (mViewports.size() - 1)) {
            mView++;
        } else {
            mView = 0;
        }
        mCurrentViewport = mViewports[mView];
        mCurrentTicks    = 0;
    } else {
        mCurrentTicks++;
    }
}

SDL_Rect
AnimatedTexture::getViewport() const {
    return mViewports[mView];
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