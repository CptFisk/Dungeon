#include <cmath>
#include <graphics/graphics.hpp>
#include <iostream>

namespace Graphics {
Graphics::Graphics(SDL_Renderer* renderer)
  : pRenderer(renderer) {}

void
Graphics::updateAnimatedTexture() {
    for (auto object : mAnimatedTextures) {
        switch ((*object)->getType()) {
            case TextureTypes::AnimatedTexture:
                static_cast<AnimatedTexture*>(*object)->updateTexture();
                break;
            case TextureTypes::Text:
                static_cast<TextTexture*>(*object)->updateTexture();
                break;
        }
    }
}

Graphics::~Graphics() {
    for (auto [name, data] : mGraphics) {
        SDL_DestroyTexture(data->getTexture());
        delete data;
    }
}

void
Graphics::init() {
    loadGraphics("rsrc");
}

TextureTypes
Graphics::getTextureType(const std::string& texture) {
    auto it = mGraphics.find(texture);
    return it != mGraphics.end() ? it->second->getType() : TextureTypes::Undefined;
}

typeTextTexture
Graphics::generateText(std::string text, const int& size) {
    /*
    int _size; // Internal variable
    if (size < 8.0f) {
        std::cerr << "Size needs to be 8.0 or bigger";
        _size = 8.0;
    } else
        _size = size;
    // //Change string to upper-case
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) { return std::toupper(c); });
    const auto textureName = "text" + text;
    if (mGraphics.find(textureName) != mGraphics.end())
        return *getTexture<typeTextTexture>(textureName);
    // Calculate sizes
    const auto length = text.length();
    const auto w      = static_cast<int>(length) * _size;
    const auto h      = _size;

    auto texture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, 255);
    // Set render target to texture instead of screen
    SDL_SetRenderTarget(pRenderer, texture);

    auto alphabet = getTexture<BaseTexture>("LettersWhite")->getTexture();
    auto numbers  = getTexture<BaseTexture>("NumbersWhite")->getTexture();

    int       pos         = 0;
    SDL_Rect  selector    = { 0, 0, 8, 8 };
    SDL_FRect destination = { 0, 0, static_cast<float>(size), static_cast<float>(size) };

    for (const auto& c : text) {
        destination.x = static_cast<float>(pos++) * size;
        if ((int)c > 0x40 && (int)c < 0x91) {
            selector.x = static_cast<float>((int)c - (0x41)) * 8.0f;
            SDL_RenderCopyF(pRenderer, alphabet, &selector, &destination);
        } else if ((int)c > 0x2F && (int)c < 0x39) {
            selector.x = static_cast<float>((int)c - (0x30)) * 8.0f;
            SDL_RenderCopyF(pRenderer, numbers, &selector, &destination);
        } else if ((int)c == 0x20) {
            selector.x = 200.0f;
            SDL_RenderCopyF(pRenderer, numbers, &selector, &destination);
        } else {
            std::cerr << "Illegal character" << std::endl;
            break;
        }
    }
    SDL_SetRenderTarget(pRenderer, nullptr); // Reset render target
    auto obj = typeTextTexture{ texture, SDL_FRect{ 0, 10, static_cast<float>(w), static_cast<float>(h) } };
    addTexture<typeTextTexture>(textureName, obj, TextureTypes::Text);
    return obj;
    */
    return typeTextTexture{};
}
}