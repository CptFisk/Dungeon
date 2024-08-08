#pragma once
#include <SDL.h>
#include <common/scale.hpp>
#include <graphics/types/baseTexture.hpp>
#include <memory>
#include <utility>
#include <vector>

namespace Graphics {
struct typeNumbersData {
    SDL_Texture*                                 Texture; // Texture
    std::vector<std::pair<SDL_FRect, SDL_Rect*>> Visuals; // Destination and viewport
};

/**
 * @brief Create a new visible number
 * @param position Position on the screen
 * @param value Value to be displayed
 * @param visibility Number of ticks it should be visible
 * @param texture Texture (font)
 * @param (optional) Scaling of texture, 1.0f = 8px;
 */
class Number {
  public:
    Number(std::pair<float, float> position, const int& value, const int& visibility, BaseTexture& texture, const float& scale = 1.0f);

    Number& operator=(const Number& other);

    bool            expired(); // Returns true if the element have expired and should be removed
    typeNumbersData getNumber();

  private:
  protected:
    int       mTicks;    // Current ticks
    const int MAX_TICKS; // Maximum ticks

    SDL_Texture*                                 pTexture;   // Reference to "font"
    std::vector<std::pair<SDL_FRect, SDL_Rect*>> mPositions; // Contains a position and  viewport
};
}