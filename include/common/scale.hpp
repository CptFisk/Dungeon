#pragma once
#include <common/structures.hpp>
#include <SDL3/SDL.h>

namespace Common{
    void calculateGameScale(Scale &scale, SDL_Window* window);
}