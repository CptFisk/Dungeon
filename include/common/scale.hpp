#pragma once
#include <common/structures.hpp>
#include <SDL.h>

namespace Common{
    void calculateGameScale(typeScale&scale, SDL_Window* window);
}