#pragma once
#include <SDL.h>
#include <global.hpp>
#include <utility>
#include <vector>

namespace Utility {
/**
 * @brief Return the center position of a SDL_FRect
 * @param rect Rectangle
 * @return
 */
std::pair<float, float>
getFRectCenter(const SDL_FRect& rect);

/**
 * @brief Return true if objects overlap
 * @return
 */
bool
isOverlapping(const SDL_FRect& obj1, const SDL_FRect& obj2);
bool
isOverlapping(const SDL_FPoint& obj1, const SDL_FRect& obj2);

/**
 * @brief Return true if 2 SDL_FRect is about to collide in a certain direction
 * @param rect1
 * @param rect2
 * @param direction
 * @return
 */
bool
isColliding(const SDL_FRect& rect1, const SDL_FRect& rect2, Orientation direction);

/**
 * @brief Return true if 2 SDL_FRect is next to each other and have the same proportions
 * @param rect1
 * @param rect2
 * @return
 */
bool
isAdjacent(const SDL_FRect& rect1, const SDL_FRect& rect2);

std::vector<SDL_FRect>
optimizeSDL_FRect(std::vector<SDL_FRect> obj);
}