#pragma once
#include <SDL.h>
#include <object/objects.hpp>
#include <stdexcept>
#include <utility>
#include <vector>

namespace Graphics {
/**
 * @brief Used for text and strings that have been generated
 */
struct typeTextTexture {
    SDL_Texture* Texture;
    SDL_FRect    Dimensions;
};

}