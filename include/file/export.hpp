#pragma once
#include <SDL.h>
#include <vector>

namespace File {

/**
 * @brief Convert a SDL_Texture* into a SDL_Surface. Memory handling and de-allocation is not handled inside function
 * @brief Errors is handled inside block and will terminate
 * @param texture SDL_Texture pointer
 * @param SDL_Renderer SDL_Renderer pointer
 * @return SDL_Surface*
 */
SDL_Surface*
textureToSurface(SDL_Texture* texture, SDL_Renderer* renderer);

static size_t writeToBuffer(SDL_RWops* context, const void* ptr, size_t size, size_t num);

bool savePngToBuffer(SDL_Surface* surface, std::vector<char>& buffer);
}