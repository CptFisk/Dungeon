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
            case TextureTypes::LightningTexture:
                static_cast<LightningTexture*>(*object)->updateTexture();
            case TextureTypes::Text:
                static_cast<TextTexture*>(*object)->updateTexture();
                break;
            case TextureTypes::Number:
                static_cast<NumberTexture*>(*object)->updateTexture();
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
}