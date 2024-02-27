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

void
Graphics::generateText(const std::string& text, const float& height) {
    auto length = text.length();
    auto width  = static_cast<float>(length) * 8.0f * mScale.ScaleX;

    auto texture = SDL_CreateTexture(
      pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, static_cast<int>(width), static_cast<int>(height * mScale.ScaleY));
    SDL_SetRenderTarget(pRenderer, texture);
    auto      alphabet = getTexture<typeSimpleTexture>("LettersWhite").Texture;
    SDL_FRect a        = { 0, 0, 8, 8 };
    SDL_FRect b        = { 8, 0, 8, 8 };
    SDL_RenderTexture(pRenderer, alphabet, &a, &a);
    SDL_RenderTexture(pRenderer, alphabet, &b, &b);
    SDL_SetRenderTarget(pRenderer, nullptr); // Reset target
    addTexture<SDL_Texture*>("AB", texture, SIMPLE_TEXTURE);
}

}