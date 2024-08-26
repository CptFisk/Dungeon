#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace Graphics {
class Font {
  public:
    Font(TTF_Font* font, const std::string& name);
    ~Font();
    /**
     * @brief Generate a sentence
     * @param sentence Sentence to be generated
     * @colour Colour of text, default is black {0,0,0,255}
     * @return SDL_Surface*&
     */
    [[nodiscard]] SDL_Surface*& generateSentence(const std::string& sentence, SDL_Color colour = { 0, 0, 0, 255 });

    /**
     * @brief Clear all generated surfaces
     */
    void clear();
    /**
     * @return Return name of the font
     */
    [[maybe_unused]] [[nodiscard]] std::string getName() const { return mName; };

  protected:
  private:
    TTF_Font*         pFont; // Reference to the font used
    const std::string mName; // Font name, mostly stored as information

    std::unordered_map<std::string, SDL_Surface*> mGenerated; // All surfaces that have been generated
};

}