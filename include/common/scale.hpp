#pragma once
#include <common/structures.hpp>
#include <SDL3/SDL.h>

namespace Common{
    void calculateGameScale(typeScale&scale, SDL_Window* window);
}