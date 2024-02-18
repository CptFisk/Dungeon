#include <cmath>
#include <graphics/graphics.hpp>
#include <iostream>

namespace Graphics {
Graphics::Graphics(SDL_Renderer* renderer, Common::Scale& scale)
  : pRenderer(renderer)
  , mScale(scale) {}

void
Graphics::updateAnimatedTexture() {
    for (auto& [name, texture] : mAnimatedTextures) {
        texture->updateTexture();
    }
}

Graphics::~Graphics() {
    // Cleaning
    for (auto [name, texture] : mTextures) {
        SDL_DestroyTexture(texture);
    }

    for (auto [name, texture] : mBaseTextures) {
        SDL_DestroyTexture(texture.Texture);
    }

    for (auto& [name, obj] : mAnimatedTextures) {
        delete obj;
    }
}

void
Graphics::init() {
    loadGraphics("rsrc");
}

SDL_Texture*
Graphics::getTexture(const std::string& name) {
    if (mTextures.find(name) != mTextures.end())
        return mTextures[name];
    if (mBaseTextures.find(name) != mBaseTextures.end())
        return mBaseTextures[name].Texture;
    if (mAnimatedTextures.find(name) != mAnimatedTextures.end())
        return mAnimatedTextures[name]->mTexture;
    return nullptr;
}

BaseTexture
Graphics::getBaseTexture(const std::string& name) {
    return mBaseTextures[name];
}

AnimatedTexture*
Graphics::getAnimatedTexture(const std::string& name) {
    return mAnimatedTextures[name];
}

void
Graphics::addTexture(const std::string& name, SDL_Texture* texture){
    mTextures[name] = texture;
}

}