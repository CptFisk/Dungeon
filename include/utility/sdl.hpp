#pragma once
#include <SDL.h>
namespace Utility{

inline constexpr SDL_Point FPointToPoint(const SDL_FPoint& point){
    return SDL_Point{static_cast<int>(point.x), static_cast<int>(point.y)};
}

inline constexpr SDL_Point addPoint(const SDL_Point& a, const SDL_Point& b){
    return {a.x + b.x, a.y + b.y};
}

inline constexpr SDL_FPoint PointToFPoint(const SDL_Point& point){
    return SDL_FPoint {static_cast<float>(point.x), static_cast<float>(point.y)};
}

inline constexpr SDL_FPoint addFPoint(const SDL_FPoint& a, const SDL_FPoint& b){
    return {a.x + b.x, a.y + b.y};
}



}