#include <error.hpp>
#include <graphics/types/font.hpp>

namespace Graphics {

Font::Font(SDL_Renderer* renderer, TTF_Font* font, const std::string& name)
  : pRenderer(renderer)
  , pFont(font)
  , mName(name) {}

Font::~Font() {
    clear();
    TTF_CloseFont(pFont);
}

SDL_Texture*&
Font::generateSentence(const std::string& sentence, SDL_Color color) {
    if (mGenerated.find(sentence) != mGenerated.end())
        return mGenerated[sentence];
    auto surface = TTF_RenderText_Solid(pFont, sentence.c_str(), color);
    ASSERT_WITH_MESSAGE(surface == nullptr, SDL_GetError())
    auto texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    ASSERT_WITH_MESSAGE(texture == nullptr, SDL_GetError())
    SDL_FreeSurface(surface); // Clear generated surface
    mGenerated[sentence] = texture;
    return mGenerated[sentence];
}

void
Font::getDimensions(int& w, int& h, SDL_Texture* texture) {
    ASSERT_WITH_MESSAGE(SDL_QueryTexture(texture, nullptr, nullptr, &w, &h) != 0, SDL_GetError())
}

void
Font::clear() {
    for (auto& [name, texture] : mGenerated)
        SDL_DestroyTexture(texture);
    mGenerated.clear();
}

}