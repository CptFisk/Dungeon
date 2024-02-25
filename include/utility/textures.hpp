#pragma once
#include <SDL3/SDL.h>
#include <utility>
#include <global.hpp>

namespace Utility{
/**
 * @brief Return the center position of a SDL_FRect
 * @param rect Rectangle
 * @return
 */
std::pair<float,float> getFRectCenter(const SDL_FRect& rect);

bool isOverlapping(const SDL_FRect& rect1, const SDL_FRect& rect2);

bool
isColliding(const SDL_FRect& rect1, const SDL_FRect& rect2, Directions direction);

bool
isAdjacent(const SDL_FRect& rect1, const SDL_FRect& rect2);

}