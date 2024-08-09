#pragma once
#include <SDL.h>
#include <array>
#include <graphics/types/texture.hpp>

namespace Graphics {
/**
 * @brief Class for letters.
 */
class LetterTexture : public Texture {
    using Texture::Texture;

  public:
    /**
     * @brief Construct a new Letter Texture object
     *
     * @param texture SDL_Texture* to use
     * @param w Width of entire picture
     * @param h Height of entire picture
     * @param renderer Reference to the renderer, used to create characters
     * @param fontW Width of invidual character
     * @param fontH Height of invidual character
     * @param length Numbers of variations for each characters
     */
    LetterTexture(SDL_Texture*  texture,
                  const int&    w,
                  const int&    h,
                  SDL_Renderer* renderer,
                  const int&    fontW,
                  const int&    fontH,
                  const int&    length);
    ~LetterTexture();

    SDL_Texture*& getLetter(const char& letter);

  protected:
  private:
    std::array<SDL_Texture*, 27> mLetters; // All invdual letters
};

}