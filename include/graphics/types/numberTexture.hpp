#pragma once
#include <SDL.h>
#include <array>
#include <graphics/types/texture.hpp>

namespace Graphics {
/**
 * @brief Class for numbers.
 */
class NumberTexture : public Texture {
    using Texture::Texture;

  public:
    /**
     * @brief Construct a new number Texture object
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
    NumberTexture(SDL_Texture*  texture,
                  const int&    w,
                  const int&    h,
                  SDL_Renderer* renderer,
                  const int&    fontW,
                  const int&    fontH,
                  const int&    length,
                  const int&    ticks);
    ~NumberTexture();
    /**
     * @brief Update the animationframe for the texture
     */
    void updateTexture();
    /**
     * @brief Returns the specified number
     *
     * @param number Image to fetch
     * @return SDL_Texture*&
     * @example getNumber(1));
     */
    [[nodiscard]] SDL_Texture*& getNumberSingle(const uint8_t& number);

    [[nodiscard]] SDL_Rect* getAnimatedViewport();

  protected:
  private:
    const int                    mTicks;
    const int                    mFontW; // Width of font
    const int                    mFontH; // Height of font
    int                          mCurrentTicks;
    int                          mView;    // Selector for viewports
    std::array<SDL_Texture*, 10> mNumbers; // All invdual number
    SDL_Rect                     mCurrentViewport;
};

}