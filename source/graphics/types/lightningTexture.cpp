#include <error.hpp>
#include <graphics/types/lightningTexture.hpp>
#include <utility/scale.hpp>

namespace Graphics {

LightningTexture::LightningTexture(SDL_Texture* texture, const int& w, const int& h, const int& ticks, const int& alpha)
  : mView(0)
  , mCycles(0)
  , mCurrentTicks(0)
  , mTicks(ticks)
  , BaseTexture(texture, w, h, TextureTypes::LightningTexture) {

    ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(BaseTexture::pTexture, SDL_BLENDMODE_BLEND) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(BaseTexture::pTexture, Utility::Scale(alpha, 0, 100, 0, 255)) != 0, SDL_GetError())
}

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
    if (mCurrentTicks > mTicks) {
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

bool
LightningTexture::done() const {
    return mView == (mViewports.size() - 1) ? true : false;
}

int
LightningTexture::getTicks() const {
    return mTicks;
}

}