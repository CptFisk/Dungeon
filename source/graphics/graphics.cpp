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
    for (auto& [name, data] : mGraphics) {
        switch (data.Type) {
            case ANIMATED_TEXTURE: {
                delete getTexture<AnimatedTexture*>(name);
            } break;
            case GENERATED_TEXTURE:
                SDL_DestroyTexture(getTexture<SDL_Texture*>(name));
                break;
            case SIMPLE_TEXTURE:
                SDL_DestroyTexture(getTexture<typeSimpleTexture>(name).Texture);
                break;
        }
    }
}

void
Graphics::init() {
    loadGraphics("rsrc");
}

}