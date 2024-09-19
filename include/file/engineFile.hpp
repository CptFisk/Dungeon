#pragma once
#include <file/types/engineLayers.hpp>

namespace File {

struct typeEngineFile {
    typeEngineLayers Layers;    //Graphical layers

    typeEngineFile()
      : Layers{} {}
};

/**
 * @brief Write data to a editor file, so it can be edited later
 * @param filename Name of the file
 * @param data Data structure
 */
void
writeEngineData(const std::string& filename, SDL_Renderer*& renderer, const Common::typeSegment& data);

}