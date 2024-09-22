#pragma once
#include <bitset>
#include <cstdint>
#include <fstream>
#include <vector>

namespace File {

/**
 * @brief Definition of a single tile. A can have multiple properties and they are each stored as a single bit in Type.
 * @brief The element Id contains a list of all Assets that is used. Since a tile can have multiple assets linked to it.
 */
struct typeTileData {
    std::bitset<32>      Type;
    std::vector<uint8_t> Base; // Assets for base texture
    std::vector<uint8_t> Top;  // Assets for overlays
    typeTileData()
      : Type(0){};
};

/**
 * @brief Structure used to store all the tiles and assets that each tile uses. This structure is only used when writing/loading a map file
 * @var Size Contains the size of x*y
 * @var Tiles Contains all the tiles.
 */
struct typeEditorTiles {
    uint16_t                  Size; // Number of tiles defined
    std::vector<typeTileData> Tiles;

    typeEditorTiles()
      : Size(0) {}

    explicit typeEditorTiles(uint16_t size)
      : Size(size) {
        Tiles.resize(size);
    }
};

/**
 * @brief Read tiles from a filestream
 */
void
readEditorTileData(std::ifstream& file, typeEditorTiles& data);

/**
 * @brief Write tiles to a filestream
 */
void
writeEditorTileData(std::ofstream& file, const typeEditorTiles& data);
}
