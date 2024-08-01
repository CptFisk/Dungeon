#pragma once
#include <bitset>
#include <cstdint>
#include <fstream>
#include <vector>

namespace Level {
/**
 * All this types is only used for generating and loading a pre-defined map file.
 */
enum TileType : uint32_t {
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
    MONSTER0     = 10,
    MONSTER1     = 11,
    MONSTER2     = 12,
    MONSTER3     = 13,
    MONSTER4     = 14,
    MONSTER5     = 15,
    MONSTER7     = 16,
    MONSTER8     = 17,
    SPARE18      = 18,
    SPARE19      = 19,
    SPARE20      = 20,
    SPARE21      = 21,
    SPARE22      = 22,
    SPARE23      = 23,
    LIGHT_YELLOW = 24,
    LIGHT_RED    = 25,
    LIGHT_WHITE  = 26,
    LIGHT_CIRCLE = 27,
    LIGHT_SQUARE = 28,
    LIGHT_SMALL  = 29,
    LIGHT_MEDIUM = 30,
    LIGHT_BIG    = 31
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
