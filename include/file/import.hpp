#pragma once
#include <SDL.h>
#include <vector>

namespace File {

/**
 * @brief Convert a SDL_Surface into a SDL_Texture*. Memory handling and de-allocation is not handled inside function
 * @brief Errors is handled inside block and will terminate
 * @param texture SDL_Surface* pointer
 * @param SDL_Renderer SDL_Renderer pointer
 * @return SDL_Texture*
 */
SDL_Texture*
surfaceToTexture(SDL_Surface* surface, SDL_Renderer*& renderer);

/**
 * @brief Create a surface from memory
 * @param data Pointer to data buffer
 * @param dataSize Size of the buffer
 * @param renderer Reference to the SDL_Renderer
 * @return
 */
SDL_Surface*
readPngFromBuffer(const char* data, const size_t dataSize, SDL_Renderer*& renderer);

}
