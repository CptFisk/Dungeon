#include <error.hpp>
#include <graphics/types/fontTTF.hpp>

namespace Graphics {

FontTTF::FontTTF(SDL_Renderer* renderer, TTF_Font* font, const std::string& name)
  : pRenderer(renderer)
  , pFont(font)
  , mName(name) {}

FontTTF::~FontTTF() {
    clear();
    if(pFont)
        TTF_CloseFont(pFont);
}

SDL_Texture*&
FontTTF::generateSentence(const std::string& sentence, SDL_Color color) {
    if (mTexts.find(sentence) != mTexts.end())
        return mTexts[sentence];
    auto surface = TTF_RenderText_Solid(pFont, sentence.c_str(), color);
    ASSERT_WITH_MESSAGE(surface == nullptr, SDL_GetError())
    auto texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    ASSERT_WITH_MESSAGE(texture == nullptr, SDL_GetError())
    SDL_FreeSurface(surface); // Clear generated surface
    mTexts[sentence] = texture;
    return mTexts[sentence];
}

[[maybe_unused]] void
FontTTF::getDimensions(int& w, int& h, SDL_Texture* texture) {
    ASSERT_WITH_MESSAGE(SDL_QueryTexture(texture, nullptr, nullptr, &w, &h) != 0, SDL_GetError())
}

void
FontTTF::clear() {
    for (auto& [name, texture] : mTexts)
        SDL_DestroyTexture(texture);
    mTexts.clear();
}

}