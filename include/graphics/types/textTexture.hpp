#pragma once
#include <SDL.h>
#include <array>
#include <graphics/types/texture.hpp>

namespace Graphics {
/**
 * @brief Class for letters.
 */
class TextTexture : public Texture {
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
     * @param ticks Number of ticks for animation
     */
    TextTexture(SDL_Texture*  texture,
                const int&    w,
                const int&    h,
                SDL_Renderer* renderer,
                const int&    fontW,
                const int&    fontH,
                const int&    length,
                const int&    ticks);
    ~TextTexture();
    /**
     * @brief Update the animationframe for the texture
     */
    void updateTexture();
    /**
     * @brief Returns the specified letter
     *
     * @param letter Image to fetch, upper and lowercase allowed
     * @return SDL_Texture*&
     * @example getLetter('A');
     */
    [[nodiscard]] SDL_Texture*& getLetterSingle(const char& letter);

    [[nodiscard]] SDL_Rect* getAnimatedViewport();

  protected:
  private:
    const int                    mTicks;
    int                          mCurrentTicks;
    int                          mView;    // Selector for viewports
    std::array<SDL_Texture*, 27> mLetters; // All invdual letters
    SDL_Rect                     mCurrentViewport;
};

}