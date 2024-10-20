#include <error.hpp>
#include <global.hpp>
#include <graphics/types/fontTexture.hpp>

namespace Graphics {
FontTexture::FontTexture(SDL_Texture* texture, SDL_Renderer*& renderer)
  : pRenderer(renderer)
  , Texture(texture, 0, 0, TextureTypes::BaseTexture) {
    static const int width  = 35 * 8;
    static const int height = 8;
    int              w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    ASSERT_WITH_MESSAGE(w != width || h != height, "Wrong size on image")
    setWidth(w);
    setHeight(h);
};

FontTexture::~FontTexture() {
    for (auto& [string, texture] : mTexts)
        SDL_DestroyTexture(texture);
    mTexts.clear();
};

SDL_Texture*&
FontTexture::generateSentence(const std::string& sentence) {
    if (mTexts.find(sentence) != mTexts.end())
        return mTexts[sentence];
    const auto length  = INT(sentence.length());
    const auto width   = length * 8;
    auto       texture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, 8);
    ASSERT_WITH_MESSAGE(texture == nullptr, SDL_GetError());
    ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, texture) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_RenderClear(pRenderer) != 0, SDL_GetError())

    ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(texture, 255) != 0, SDL_GetError())
    auto destination = SDL_Rect{ 0, 0, 8, 8 };
    auto source      = SDL_Rect{ 0, 0, 8, 8 };
    for (auto c : sentence) {
        SDL_RenderCopy(pRenderer, pTexture, &source, &destination);
        destination.x += 8;
    }
    // Reset renderer
    ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, nullptr) != 0, SDL_GetError())
    mTexts[sentence] = texture;
    return mTexts[sentence];
}

}