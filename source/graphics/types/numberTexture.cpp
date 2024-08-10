#include <error.hpp>
#include <graphics/types/numberTexture.hpp>

namespace Graphics {

NumberTexture::NumberTexture(SDL_Texture*  texture,
                             const int&    w,
                             const int&    h,
                             SDL_Renderer* renderer,
                             const int&    fontW,
                             const int&    fontH,
                             const int&    length,
                             const int&    ticks)
  : mView(0)
  , mCurrentTicks(0)
  , mTicks(ticks)
  , Texture(texture, w, h, TextureTypes::Number) {
    const int expectedLength = (26 * fontW) + fontW; // We also add for space
    const int expectedHeight = length * fontH;
    ASSERT_WITH_MESSAGE(expectedLength != w || expectedHeight != h, "Size dont match on NumberTexture")

    for (int i = 0; i < mNumbers.size(); i++) {
        // Area were we fetch each character from
        auto area    = SDL_Rect{ i * fontW, 0, fontW, fontH };
        auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, fontW, fontH);

        ASSERT_WITH_MESSAGE(texture == nullptr, SDL_GetError());
        ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(renderer, texture) != 0, SDL_GetError())
        ASSERT_WITH_MESSAGE(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0) != 0, SDL_GetError())
        ASSERT_WITH_MESSAGE(SDL_RenderClear(renderer) != 0, SDL_GetError())
        ASSERT_WITH_MESSAGE(SDL_RenderCopy(renderer, texture, &area, nullptr) != 0, SDL_GetError())
        ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(renderer, nullptr) != 0, SDL_GetError())

        mNumbers[i] = texture;
    }
    // Creating viewports
    int viewports = (h / fontH);

    for (int i = 0; i < viewports; i++) {
        auto area = SDL_Rect{ 0, i * fontH, fontW, (i * fontH) + fontH };
        addViewport(area);
    }
};

NumberTexture::~NumberTexture() {
    for (auto number : mNumbers)
        SDL_DestroyTexture(number);
};

SDL_Texture*&
NumberTexture::getNumberSingle(const uint8_t& number) {
    ASSERT_WITH_MESSAGE(number > 9 || number < 0, "Wrong value on number")
    return mNumbers[number];
}

SDL_Rect*
NumberTexture::getAnimatedViewport() {
    return &mCurrentViewport;
}

void
NumberTexture::updateTexture() {
    if (mCurrentTicks > mTicks) {
        if (mView < (mViewports.size() - 1))
            mView++;
        else
            mView = 0;
        mCurrentViewport = mViewports[mView];
        mCurrentTicks    = 0;
    } else
        mCurrentTicks++;
}

}