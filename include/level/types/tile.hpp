#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

namespace Level::File {
/**
 * All this types is only used for generating and loading a pre-defined map file.
 */
enum class TileType : uint8_t {
    BLANK            = 0,      // Not defined
    TEXTURE          = 1 << 0, // Standard SDL_Texture*
    ANIMATED_TEXTURE = 1 << 1, // Class AnimatedTexture
    WALL             = 1 << 2, // Blocks all movement
    OBSTACLE         = 1 << 3, // Possible to "fly" over
    UP               = 1 << 4, // Warp the player down one Z-layer
    DOWN             = 1 << 5  // Warp the player up one Z-layer
};

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
    uint16_t                  TileSize; // Number of tiles defined
    std::vector<typeTileData> Tiles;
    uint16_t                  LayerSize;
    std::vector<uint8_t>      TopLayer;

    typeTiles()
      : TileSize(0)
      , LayerSize(0) {}

    explicit typeTiles(uint16_t size)
      : TileSize(size)
      , LayerSize(size) {
        Tiles.resize(size);
        TopLayer.resize(size);
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
