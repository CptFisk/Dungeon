#pragma once
#include <bitset>
#include <cstdint>
#include <fstream>
#include <vector>

namespace Level::File {
/**
 * All this types is only used for generating and loading a pre-defined map file.
 */
enum TileType : uint8_t {
    BASE_TEXTURE = 0, // Textures for base-layer
    TOP_TEXTURE  = 1, // Class AnimatedTexture
    WALL         = 2, // Blocks all movement
    OBSTACLE     = 3, // Possible to "fly" over
    UP           = 4, // Warp the player down one Z-layer
    DOWN         = 5, // Warp the player up one Z-layer
    SPARE6       = 6,
    SPARE7       = 7,
    SPARE8       = 8,
    SPARE9       = 9,
    SPARE10      = 10,
    SPARE11      = 11,
    SPARE12      = 12,
    SPARE13      = 13,
    SPARE14      = 14,
    SPARE15      = 15,
    SPARE16      = 16,
    SPARE17      = 17,
    SPARE18      = 18,
    SPARE19      = 19,
    SPARE20      = 20,
    SPARE21      = 21,
    SPARE22      = 22,
    SPARE23      = 23,
    SPARE24      = 24,
    LIGHT_YELLOW = 25,
    LIGHT_RED    = 26,
    LIGHT_WHITE  = 27,
    LIGHT_CIRCLE = 28,
    LIGHT_SQUARE = 29,
    LIGHT_SMALL  = 30,
    LIGHT_MEDIUM = 31,
    LIGHT_BIG    = 32
};

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
struct typeTiles {
    uint16_t                  Size; // Number of tiles defined
    std::vector<typeTileData> Tiles;

    typeTiles()
      : Size(0) {}

    explicit typeTiles(uint16_t size)
      : Size(size) {
        Tiles.resize(size);
    }
};

/**
 * @brief Read tiles from a filestream
 */
void
readTileData(std::ifstream& file, typeTiles& data);

/**
 * @brief Write tiles to a filestream
 */
void
writeTileData(std::ofstream& file, const typeTiles& data);
}
