#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <common/scale.hpp>
#include <error.hpp>
#include <string>
#include <vector>

namespace Common {

// Help function to calculate a new rectangle based on x and y position
SDL_FRect
newSDL_FRect(const std::pair<int, int>& coords);
SDL_FRect
newSDL_FRect(const int& x, const int& y);
SDL_FRect
newSDL_FRect(const float& x, const float& y);
SDL_FRect
newSDL_FRectScaled(const int& x, const int& y, const typeScale& scale);
SDL_FRect
newSDL_FRectScaled(const float& x, const float& y, const typeScale& scale);

/**
 * @brief Load a valid image file and return a SDL_Texture*
 * @param renderer Reference to the render
 * @param filename File path
 * @return SDL_Texture*, if error the program will terminate
 */
SDL_Texture*
loadImage(SDL_Renderer* renderer, const std::string& filename);

/**
 * @brief Load a valid .ttf font and return a TTF_Font*
 * @param path File path
 * @param size Font size in DPI
 * @return TTF_Font*, if error the program will terminate
 */
TTF_Font*
loadFont(const std::string& path, const int& size);


}
