#pragma once
#include <SDL3/SDL.h>
#include <common/scale.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/structures.hpp>

namespace Player {
class Indicator {
  public:
    /**
     * @brief Constructor for health icon and numbers
     * @param visible Shall UI be visible
     * @param value Current health
     * @param distance Distance from bottom of screen
     * @param renderer Pointer to renderer
     * @param scale Game scale factor
     * @param texture Texture
     */
    Indicator(bool&                              visible,
              int&                               value,
              const float&                       distance,
              SDL_Renderer*                      renderer,
              Graphics::AnimatedTexture*         texture,
              const Graphics::typeSimpleTexture& numbers);
    void draw();

  protected:
  private:
    const SDL_FRect    mPositionIcon;      // Position of icon
    const SDL_FRect    mPositionNumber[3]; // Position for numbers
    bool&              mVisible;           // If the UI should be visible
    int&               mValue;             // Players current health

    Graphics::AnimatedTexture*  pIconTexture; // Texture for the icon
    Graphics::typeSimpleTexture mNumbers;     // Textures for numbers

    SDL_Renderer* pRenderer; // Reference to renderer
};
}