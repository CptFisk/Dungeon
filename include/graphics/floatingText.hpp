#pragma once
#include <SDL.h>
#include <common/scale.hpp>
#include <graphics/types/drawData.hpp>
#include <memory>
#include <utility>
#include <vector>

namespace Graphics {
/**
 * @brief Create a new visible number
 * @param position Position on the screen
 * @param value Value to be displayed
 * @param visibility Number of ticks it should be visible
 * @param texture Texture (font)
 * @param (optional) Scaling of texture, 1.0f = 8px;
 */
class FloatingText {
  public:
    FloatingText(SDL_FPoint position, const int& value, const int& visibility, SDL_Texture*& texture, const float& scale = 1.0f);

    FloatingText& operator=(const FloatingText& other);

    bool         expired(); // Returns true if the element have expired and should be removed
    typeDrawData getFloatingText();

  private:
  protected:
    int       mTicks;    // Current ticks
    const int mMaxTicks; // Maximum ticks

    SDL_Texture* pTexture; // Reference to "font"
    SDL_FRect    mPosition;
};
}