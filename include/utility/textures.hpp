#pragma once
#include <SDL3/SDL.h>
#include <utility>

namespace Utility{
/**
 * @brief Return the center position of a SDL_FRect
 * @param rect Rectangle
 * @return
 */
std::pair<float,float> getFRectCenter(const SDL_FRect& rect);
}