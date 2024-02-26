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
    for (auto& [name, data] : mGraphics) {
        switch (data.Type) {
            case ANIMATED_TEXTURE: {
                auto obj = getTexture<AnimatedTexture>(name);
            } break;
            case GENERATED_TEXTURE:
                SDL_DestroyTexture(getTexture<SDL_Texture*>(name));
                break;
            case SIMPLE_TEXTURE:

                break;
        }
    }

    printf("Cleaned: %i \n", cleaned);
}

void
Graphics::init() {
    loadGraphics("rsrc");
}

}