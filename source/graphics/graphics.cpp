#include <graphics/graphics.hpp>
#include <iostream>
#include <set>
namespace Graphics {
Graphics::Graphics(SDL_Renderer* renderer)
  : pRenderer(renderer) {}

void
Graphics::updateAnimatedTexture() {
    for (auto object : mAnimatedTextures) {
        switch ((*object)->getType()) {
            case TextureTypes::AnimatedTexture:
                dynamic_cast<AnimatedTexture*>(*object)->updateTexture();
                break;
            case TextureTypes::LightningTexture:
                dynamic_cast<LightningTexture*>(*object)->updateTexture();
                break;
            case TextureTypes::Text:
                dynamic_cast<TextTexture*>(*object)->updateTexture();
                break;
            case TextureTypes::Number:
                dynamic_cast<NumberTexture*>(*object)->updateTexture();
                break;
            default:
                ASSERT_WITH_MESSAGE(true, "Wrong type!")
        }
    }
}

Graphics::~Graphics() {
    SDL_RenderClear(pRenderer);
    for (auto& [name, data] : mGraphics) {
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