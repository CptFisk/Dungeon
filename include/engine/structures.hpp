#pragma once
#include <SDL.h>
#include <vector>

namespace Engine {

struct typeSegment {
    std::vector<SDL_Texture*> Layers;
    SDL_FRect    Position;
};
}