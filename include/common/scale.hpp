#pragma once
#include <SDL.h>

namespace Common {
/**
 * @brief Structure that contains all information about SDL_Window.
 * @brief The factor X and Y is a calculated value that shall be multiplied to accomplish
 * @brief a grid size of 16x12 squares.
 */
struct typeScale {
    float factorX;             // Value used to scale the width of each level, 1 means 16 squares width
    float factorY;             // Value used to scale the height of each level, 1 means 16 squares width
    int   windowWidth;         // Window width
    float windowWidthF;        // Window width (float)
    int   windowHeight;        // Window Height
    float windowHeightF;       // Window width (float)
    int   scaledWindowWidth;    // Width of scaled window
    float scaledWindowWidthF;  // Width of scaled window (float)
    int   scaledWindowHeight;  // Height of scaled window
    float scaledWindowHeightF; // Height of scaled window (float)
    float selectedScale;       // Scale that we stick with
    typeScale()
      : factorX(0.0f)
      , factorY(0.0f)
      , windowWidth(0)
      , windowHeight(0)
      , windowWidthF(0.0f)
      , windowHeightF(0.0f)
      , scaledWindowHeight(0)
      , scaledWindowHeightF(0.0f)
      , scaledWindowWidth(0)
      , scaledWindowWidthF(0.0f)
      , selectedScale(0.0f) {}
};

void
calculateGameScale(typeScale& scale, SDL_Window* window);
}