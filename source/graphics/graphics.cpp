#include <cmath>
#include <graphics/graphics.hpp>
#include <iostream>

namespace Graphics {
Graphics::Graphics(SDL_Renderer* renderer, Engine::Scale& scale)
  : pRenderer(renderer)
  , mScale(scale){
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
Graphics::init() {
    loadGraphics("rsrc");
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