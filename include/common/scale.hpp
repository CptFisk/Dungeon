#pragma once
#include <SDL.h>

namespace Common {
/**
 * @brief Structure that contains all information about SDL_Window.
 * @brief The factor X and Y is a calculated value that shall be multiplied to accomplish
 * @brief a grid size of 16x12 squares.
 */
struct typeScale {
    float factorX;
    float factorY;
    int   windowWidth;   // Window width
    int   windowHeight;  // Window Height
    float selectedScale; // Slace that we stick with
    typeScale()
      : factorX(0.0f)
      , factorY(0.0f)
      , windowWidth(0)
      , windowHeight(0)
      , selectedScale(0.0f) {}
};

void
calculateGameScale(typeScale& scale, SDL_Window* window);
}