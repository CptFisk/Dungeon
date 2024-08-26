#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace Graphics {
class Font {
  public:
    Font(SDL_Renderer* renderer, TTF_Font* font, const std::string& name);
    ~Font();
    /**
     * @brief Generate a sentence
     * @param sentence Sentence to be generated
     * @colour Colour of text, default is black {0,0,0,255}
     * @return SDL_Texture*&
     */
    [[nodiscard]] SDL_Texture*& generateSentence(const std::string& sentence, SDL_Color colour = { 0, 0, 0, 255 });
    /**
     * @brief Get text dimenstions
     * @param w
     * @param h
     */
    static void getDimensions(int& w, int& h, SDL_Texture*);
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
    SDL_Renderer*     pRenderer; // Used for creating new textures
    TTF_Font*         pFont;     // Reference to the font used
    const std::string mName;     // Font name, mostly stored as information

    std::unordered_map<std::string, SDL_Texture*> mGenerated; // All textures that have been generated
};

}