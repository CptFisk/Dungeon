#include <graphics/types/font.hpp>
#include <error.hpp>

namespace Graphics {

Font::Font(TTF_Font* font, const std::string& name)
  : pFont(font)
  , mName(name) {}

Font::~Font() {
    clear();
    TTF_CloseFont(pFont);
}

SDL_Surface*&
Font::generateSentence(const std::string& sentence, SDL_Color color) {
    if(mGenerated.find(sentence) != mGenerated.end())
        return mGenerated[sentence];
    auto surface = TTF_RenderText_Solid(pFont, sentence.c_str(), color);
    ASSERT_WITH_MESSAGE(surface == nullptr, SDL_GetError())
    mGenerated[sentence] = surface;
    return mGenerated[sentence];
}

void
Font::clear() {
    for(auto &[name, surface] : mGenerated)
        SDL_FreeSurface(surface);
    mGenerated.clear();
}

}