#pragma once
#include <cstdint>
namespace Common{
/**
 * @brief All the different properties a tile can have. Note that there might be difference between engine and editor

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
}