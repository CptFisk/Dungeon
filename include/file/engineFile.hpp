#pragma once
#include <file/types/engineLayers.hpp>
#include <file/types/engineTile.hpp>
#include <file/types/header.hpp>

namespace File {

struct typeEngineFile {
    typeHeaderData               Header; // Header, common for all files
    typeEngineLayers             Layers; // Graphical layers
    std::vector<std::bitset<32>> Tiles;  // Optimal tile structure
    typeEngineFile()
      : Header{}
      , Layers{}
      , Tiles{} {}
};

typeEngineFile
readEngineData(const std::string& filename, SDL_Renderer*& renderer);

/**
 * @brief Write data to a editor file, so it can be edited later
 */
void
writeEngineData(const std::string&         filename,
                SDL_Renderer*&             renderer,
                const typeHeaderData&      header,
                const Common::typeSegment& data,
                const typeEditorTiles&     tiles);

}