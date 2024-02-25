#include "utility/textures.hpp"

namespace Utility {

std::pair<float, float>
getFRectCenter(const SDL_FRect& rect) {
    return std::pair<float, float>{ rect.x + (rect.w / 2.0), rect.y + (rect.h / 2) };
}

bool
isOverlapping(const SDL_FRect& rect1, const SDL_FRect& rect2) {
    return !(rect1.x + rect1.w < rect2.x || rect1.x > rect2.x + rect2.w || rect1.y + rect1.h < rect2.y ||
             rect1.y > rect2.y + rect2.h);
}

bool
isColliding(const SDL_FRect& rect1, const SDL_FRect& rect2, Directions direction) {
    SDL_FRect tmp = rect1;
    switch (direction) {
        case North:
            tmp.y -= 3.0f;
            break;
        case East:
            tmp.x += 3.0f;
            break;
        case South:
            tmp.y += 3.0f;
            break;
        case West:
            tmp.x -= 3.0f;
            break;
    }
    return isOverlapping(tmp, rect2);
}

bool
isAdjacent(const SDL_FRect& rect1, const SDL_FRect& rect2) {
    return (rect1.x == rect2.x && rect1.y == rect2.y && rect1.h == rect2.h) ||
           (rect1.y == rect2.y && rect1.x == rect2.x && rect1.w == rect2.w);
}
}