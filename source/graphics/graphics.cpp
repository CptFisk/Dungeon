#include <cmath>
#include <graphics/graphics.hpp>
#include <iostream>

namespace Graphics {
Graphics::Graphics(SDL_Renderer* renderer, float& scaleX, float& scaleY)
  : pRenderer(renderer)
  , mScaleX(scaleX)
  , mScaleY(scaleY) {
    loadGraphics("rsrc");
}

void
Graphics::updateAnimatedTexture() {
    for(auto &[name, texture] : mAnimatedTextures){
        texture->updateTexture();
    }
}

Graphics::~Graphics() {
    for (auto [name, texture] : mTextures) {
        SDL_DestroyTexture(texture);
    }

    for (auto &[name, obj] : mAnimatedTextures) {
        delete obj;
    }
}

void
Graphics::generateSquare(const std::string& name,
                         const int&         width,
                         const int&         height,
                         const Uint8&       r,
                         const Uint8&       g,
                         const Uint8&       b,
                         const Uint8&       a) {
    auto surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
    SDL_FillSurfaceRect(surface, nullptr, SDL_MapRGB(surface->format, r, g, b));
    auto square = SDL_CreateTextureFromSurface(pRenderer, surface);
    SDL_SetTextureBlendMode(square, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(square, a);
    SDL_DestroySurface(surface);
    mTextures[name] = square;
}

SDL_Texture*
Graphics::getTexture(const std::string& name) {
    return mTextures[name];
}

BaseTexture
Graphics::getBaseTexture(const std::string& name) {
    return mBaseTextures[name];
}

AnimatedTexture*
Graphics::getAnimatedTexture(const std::string& name) {
    return mAnimatedTextures[name];
}

}