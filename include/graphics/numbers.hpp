#pragma once
#include <SDL3/SDL.h>
#include <common/scale.hpp>
#include <graphics/structures.hpp>
#include <utility>
#include <vector>

namespace Graphics {
struct typeNumbersData {
    SDL_Texture*                                  Texture; // Texture
    std::vector<std::pair<SDL_FRect, SDL_FRect*>> Visuals; // Destination and viewport
};

/**
 * @brief Class used to display a number for a period of time
 */
class Number {
  public:
    /**
     * @brief Create a new visible number
     * @param position Position on the screen
     * @param value Value to be displayed
     * @param visibility Number of ticks it should be visible
     * @param texture Texture (font)
     * @param size Size of each number, scale is added automatically
     * @param scale Current scale on the screen
     */
    Number(std::pair<float, float>  position,
           const int&               value,
           const int&               visibility,
           typeSimpleTexture        texture,
           const float&             size,
           const Common::typeScale& scale);

    bool expired(); // Returns true if the element have expired and should be removed
    typeNumbersData getNumber() const;
  private:
  protected:
    int       mTicks;    // Current ticks
    const int MAX_TICKS; // Maximum ticks

    SDL_Texture*                                  pTexture;   // Reference to "font"
    std::vector<std::pair<SDL_FRect, SDL_FRect*>> mPositions; // Contains a position and  viewport
};
}