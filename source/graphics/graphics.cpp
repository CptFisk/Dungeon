#include <cmath>
#include <graphics/graphics.hpp>
#include <iostream>

namespace Graphics {
Graphics::Graphics(SDL_Renderer* renderer, Common::typeScale& scale)
  : pRenderer(renderer)
  , mScale(scale) {}

void
Graphics::updateAnimatedTexture() {

    for (auto& texture : mAnimatedTextures) {
        texture->updateTexture();
    }

}

Graphics::~Graphics() {
    int cleaned = 0;
    // Cleaning


    printf("Cleaned: %i \n", cleaned);
}

void
Graphics::init() {
    loadGraphics("rsrc");
}

}