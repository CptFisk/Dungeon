#pragma once
#include <SDL.h>
#include <common/segmentType.hpp>
#include <cstdint>
#include <fstream>
#include <vector>

namespace File {

struct typeEngineLayers {
    std::vector<SDL_Texture*> Bottom;    // Data in bottom layer
    std::vector<SDL_Texture*> Top;       // Data in top layer
    std::vector<SDL_Texture*> Lightning; // Data in lightning layer
    typeEngineLayers() = default;
};

/**
 * @brief Read layers from a filestream
 */
void
readEngineLayers(std::ifstream& file, SDL_Renderer*& renderer, typeEngineLayers& data);

void
readLayer(std::ifstream& file, SDL_Renderer*& renderer, std::vector<SDL_Texture*>& data);
/**
 * @brief Write all layers to a file, using some help functions from Common
 */
void
writeEngineLayers(std::ofstream& file, SDL_Renderer*& renderer, const Common::typeSegment& data);
/**
 * @brief Helper function to simplify code
 * @param file Reference to ofstream
 * @param renderer Reference to the SDL_Renderer, used for converting to SDL_Surface*
 * @param data Layer data
 */
void
writeLayer(std::ofstream& file, SDL_Renderer*& renderer, const Common::typeSegmentData& data);
}