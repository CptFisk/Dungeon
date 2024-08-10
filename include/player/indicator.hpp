#pragma once
#include <SDL.h>
#include <common/scale.hpp>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/numberTexture.hpp>

namespace Player {
class Indicator {
  public:
    Indicator(bool&                      visible,
              int&                       value,
              const float&               distance,
              SDL_Renderer*              renderer,
              Graphics::AnimatedTexture* texture,
              Graphics::NumberTexture*   numbers);
    void draw();

  protected:
  private:
    const SDL_FRect mPositionIcon;      // Position of icon
    const SDL_FRect mPositionNumber[3]; // Position for numbers
    bool&           mVisible;           // If the UI should be visible
    int&            mValue;             // Players current health

    Graphics::AnimatedTexture* pIconTexture; // Texture for the icon
    Graphics::NumberTexture*   pNumbers;     // Textures for numbers

    SDL_Renderer* pRenderer; // Reference to renderer
};
}