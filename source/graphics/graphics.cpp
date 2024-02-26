#include <cmath>
#include <graphics/graphics.hpp>
#include <iostream>

namespace Graphics {
Graphics::Graphics(SDL_Renderer* renderer, Common::typeScale& scale)
  : pRenderer(renderer)
  , mScale(scale) {}

void
Graphics::updateAnimatedTexture() {
    for (auto& [name, texture] : mAnimatedTextures) {
        texture->updateTexture();
    }
}

Graphics::~Graphics() {
    int cleaned = 0;
    // Cleaning
    for (auto [name, texture] : mTextures) {
        SDL_DestroyTexture(texture);
        cleaned++;
    }

    for (auto [name, texture] : mBaseTextures) {
        SDL_DestroyTexture(texture.Texture);
        cleaned++;
    }

    for (auto& [name, obj] : mAnimatedTextures) {
        delete obj;
        cleaned++;
    }
    printf("Cleaned: %i \n", cleaned);
}

void
Graphics::init() {
    loadGraphics("rsrc");
}

}