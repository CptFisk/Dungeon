#pragma once
#include <file/types/engineLayers.hpp>
#include <file/types/header.hpp>

namespace File {

struct typeEngineFile {
    typeHeaderData   Header; // Header, common for all files
    typeEngineLayers Layers; // Graphical layers

    typeEngineFile()
      : Header{}
      , Layers{} {}
};

/**
 * @brief Write data to a editor file, so it can be edited later
 * @param filename Name of the file
 * @param data Data structure
 */
void
writeEngineData(const std::string& filename, SDL_Renderer*& renderer, const typeHeaderData& header, const Common::typeSegment& data);

}