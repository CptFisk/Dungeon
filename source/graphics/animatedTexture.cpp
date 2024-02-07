#include <graphics/animatedTexture.hpp>

namespace Graphics {
AnimatedTexture::AnimatedTexture()
  : mView(0)
  , mTexture(nullptr) {}

AnimatedTexture::AnimatedTexture(SDL_Texture* texture)
  : mTexture(texture)
  , mView(0) {}

AnimatedTexture::~AnimatedTexture() {
    SDL_DestroyTexture(mTexture); // Cleaning
}


SDL_Texture*
AnimatedTexture::getTexture() {
    return mTexture;
}

SDL_FRect*
AnimatedTexture::getViewport() {
    return &mCurrentViewport;
}

void
AnimatedTexture::addViewport(const SDL_FRect& view) {
    mViewports.push_back(view);
    mCurrentViewport = mViewports.front();
}

void
AnimatedTexture::nextViewport() {
    if(mView < (mViewports.size() - 1)){
        mView++;
    }else{
        mView = 0;
    }
    mCurrentViewport = mViewports[mView];
}

SDL_FRect
AnimatedTexture::getViewport() const {
    return mViewports[mView];
}
}