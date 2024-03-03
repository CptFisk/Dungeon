#pragma once
#include <SDL3/SDL.h>
#include <common/scale.hpp>

namespace Common {

// Help function to calculate a new rectangle based on x and y position
SDL_FRect
newSDL_FRect(const int& x, const int& y);
SDL_FRect
newSDL_FRect(const float& x, const float& y);

}
