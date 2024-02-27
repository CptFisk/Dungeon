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
            case SDL_TEXTURE:
                SDL_DestroyTexture(getTexture<SDL_Texture*>(name));
                break;
            case TEXT:
                SDL_DestroyTexture(getTexture<typeTextTexture>(name).Texture);
                break;
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

typeTextTexture
Graphics::generateText(std::string text, const float& width, const float& height) {
    // //Change string to upper-case
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) { return std::toupper(c); });
    const auto textureName = "text" + text;
    if (mGraphics.find(textureName) != mGraphics.end())
        return getTexture<typeTextTexture>(textureName);
    // Calculate sizes
    const auto length = text.length();
    const auto w      = static_cast<int>(length) * static_cast<int>(width * mScale.ScaleX);
    const auto h      = static_cast<int>(height * mScale.ScaleY);

    auto texture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, 255);
    // Set render target to texture instead of screen
    if(SDL_SetRenderTarget(pRenderer, texture) != 0)
        std::cout << SDL_GetError() << std::endl;

    auto alphabet = getTexture<typeSimpleTexture>("LettersWhite").Texture;

    int       pos         = 0;
    SDL_FRect selector    = { 0, 0, 8.0f, 8.0f };
    SDL_FRect destination = { 0, 0, width * mScale.ScaleX, height * mScale.ScaleY };
    for (const auto& c : text) {
        if ((int)c > 0x40 && (int)c < 0x91) {
            selector.x = static_cast<float>((int)c - (0x41)) * 8.0f;
            selector.y = 0;
        } else if ((int)c > 0x2F && (int)c < 0x39) {
            selector.x = static_cast<float>((int)c - (0x30)) * 8.0f;
            selector.y = 8;
        } else {
            std::cerr << "Illegal character" << std::endl;
            break;
        }
        destination.x = static_cast<float>(pos++) * width * mScale.ScaleX;
        SDL_RenderTexture(pRenderer, alphabet, &selector, &destination);
    }
    SDL_SetRenderTarget(pRenderer, nullptr); // Reset render target
    auto obj = typeTextTexture{ texture, SDL_FRect{ 0, 0, static_cast<float>(w), static_cast<float>(h) } };
    addTexture<typeTextTexture>(textureName, obj, TEXT);
    return obj;
}

}