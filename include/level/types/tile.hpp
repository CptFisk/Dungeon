#pragma once
#include <cstdint>

namespace Level::File{
/**
 * All this types is only used for generating and loading a pre-defined map file.
 */
enum class TileType : uint8_t { BLANK = 0, TEXTURE = 1 << 0, WALL = 1 << 1, OBSTACLE = 1 << 2 };

/**
 * @brief Definition of a single tile. A can have multiple properties and they are each stored as a single bit in Type.
 * @brief The element Id contains a list of all Assets that is used. Since a tile can have multiple assets linked to it.
 */
struct typeTileData {
    uint8_t              Type; // Tiletype
    std::vector<uint8_t> Id;   // Reference to assets. Drawn from bottom to top
    typeTileData()
      : Type(0){};
};

/**
 * @brief Structure used to store all the tiles and assets that each tile uses. This structure is only used when writing/loading a map file
 * @var Size Contains the size of x*y
 * @var Tiles Contains all the tiles.
 */
struct typeTiles {
    uint16_t                  Size; // Number of tiles defined
    std::vector<typeTileData> Tiles;

    // Constructor
    explicit typeTiles(uint16_t size)
      : Size(size) {
        Tiles.resize(size);
    }
};
}
