#include <graphics/graphics.hpp>
#include <iostream>
#include <set>
namespace Graphics {
Graphics::Graphics(SDL_Renderer* renderer)
  : pRenderer(renderer) {
    loadGraphics("rsrc");
}

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
    for(auto& [name, data] : mFontsTTF)
        delete data;
}

Texture*
Graphics::getTexture(const std::string& name) {
    ASSERT_WITH_MESSAGE(mGraphics.find(name) == mGraphics.end(), name << " dont exist");
    return mGraphics[name];
}

SDL_Texture*
Graphics::getSentence(const std::string& name, const std::string& sentence, const SDL_Color& color) {
    ASSERT_WITH_MESSAGE(mFontsTTF.find(name) == mFontsTTF.end(), "Font dont exist")
    return mFontsTTF[name]->generateSentence(sentence, color);
}

void
Graphics::addTexture(const std::string& name, Texture* texture) {
    ASSERT_WITH_MESSAGE(mGraphics.find(name) != mGraphics.end(), name << " already exists")

    switch (texture->getType()) {
        case TextureTypes::GeneratedTexture:
        case TextureTypes::BaseTexture:
        case TextureTypes::UserInterface:
            mGraphics[name] = texture;
            break;
        case TextureTypes::AnimatedTexture:
        case TextureTypes::LightningTexture:
            mGraphics[name] = texture;
            mAnimatedTextures.push_back(&mGraphics[name]);
            break;
        default:
            ASSERT_WITH_MESSAGE(true, "Cant get type")
    }
}

void
Graphics::addTTFFont(const std::string& name, FontTTF* font) {
    ASSERT_WITH_MESSAGE(mFontsTTF.find(name) != mFontsTTF.end(), name << " already exist")
    mFontsTTF[name] = font;
}

FontTTF*
Graphics::getTTFFont(const std::string& name) {
    ASSERT_WITH_MESSAGE(mFontsTTF.find(name) == mFontsTTF.end(), name << " dont exist");
    return mFontsTTF[name];
}

TextureTypes
Graphics::getTextureType(const std::string& texture) {
    auto it = mGraphics.find(texture);
    return it != mGraphics.end() ? it->second->getType() : TextureTypes::Undefined;
}
}