#include "utility/textures.hpp"

namespace Utility {

std::pair<float, float>
getFRectCenter(const SDL_FRect& rect) {
    return std::pair<float, float>{ rect.x + (rect.w / 2.0), rect.y + (rect.h / 2) };
}

bool
isOverlapping(const SDL_FRect& obj1, const SDL_FRect& obj2) {
    return !(obj1.x + obj1.w < obj2.x || obj1.x > obj2.x + obj2.w || obj1.y + obj1.h < obj2.y || obj1.y > obj2.y + obj2.h);
}

bool isOverlapping(const SDL_FPoint& obj1, const SDL_FRect& obj2){
    return !(obj1.x + 1 < obj2.x || obj1.x > obj2.x + obj2.w || obj1.y + 1 < obj2.y || obj1.y > obj2.y + obj2.h);
}

bool
isColliding(const SDL_FRect& rect1, const SDL_FRect& rect2, Orientation direction) {
    SDL_FRect tmp = rect1;
    const float threshold = 1.0f;
    switch (direction) {
        case North:
            tmp.y -= threshold;
            break;
        case East:
            tmp.x += threshold;
            break;
        case South:
            tmp.y += threshold;
            break;
        case West:
            tmp.x -= threshold;
            break;
        case All:
        default:
            break;
    }
    return isOverlapping(tmp, rect2);
}

bool
isAdjacent(const SDL_FRect& rect1, const SDL_FRect& rect2) {
    const auto& obj1 = (rect1.x < rect2.x || (rect1.x == rect2.x && rect1.y < rect2.y)) ? rect1 : rect2;
    const auto& obj2 = (&obj1 == &rect1) ? rect2 : rect1;

    return ((obj1.x + obj1.w == obj2.x && obj1.y == obj2.y && obj1.h == obj2.h) || // Vertical adjacency
            (obj1.y + obj1.h == obj2.y && obj1.x == obj2.x && obj1.w == obj2.w));  // Horizontal adjacency
}

std::vector<SDL_FRect>
optimizeSDL_FRect(std::vector<SDL_FRect> obj) {
    std::vector<bool> used(obj.size(), false);

    for (auto i = 0; i < obj.size(); ++i) {
        if (used[i])
            continue;

        for (auto j = i + 1; j < obj.size(); ++j) {
            if (used[j])
                continue;

            if (isAdjacent(obj[i], obj[j])) {
                SDL_FRect optimized;
                optimized.x = std::min(obj[i].x, obj[j].x);
                optimized.y = std::min(obj[i].y, obj[j].y);
                optimized.w = (obj[i].x == obj[j].x) ? (obj[i].w + obj[j].w) : obj[i].w;
                optimized.h = (obj[i].y == obj[j].y) ? (obj[i].h + obj[j].h) : obj[i].h;
                obj[i]      = optimized;
                used[j]     = true;
            }
        }
    }
    std::vector<SDL_FRect> optimized;
    for (auto i = 0; i < obj.size(); ++i) {
        if (!used[i])
            optimized.push_back(obj[i]);
    }

    return optimized;
}
}