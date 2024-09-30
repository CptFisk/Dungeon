#pragma once
#include <cstdint>
namespace Common {
/**
 * @brief All the different properties a tile can have. Note that there might be difference between engine and editor

 */
enum TileType : uint32_t {
    BASE_TEXTURE [[maybe_unused]] = 0, // Textures for base-layer
    TOP_TEXTURE [[maybe_unused]]  = 1, // Class AnimatedTexture
    WALL [[maybe_unused]]         = 2, // Blocks all movement
    OBSTACLE [[maybe_unused]]     = 3, // Possible to "fly" over
    UP [[maybe_unused]]           = 4, // Warp the player down one Z-layer
    DOWN [[maybe_unused]]         = 5, // Warp the player up one Z-layer
    NPC_WALL [[maybe_unused]]     = 6, // Wall that NPC cant move pass
    SPARE7 [[maybe_unused]]       = 7,
    SPARE8 [[maybe_unused]]       = 8,
    SPARE9 [[maybe_unused]]       = 9,
    // Monster bits
    MONSTER0 [[maybe_unused]] = 10,
    MONSTER1 [[maybe_unused]] = 11,
    MONSTER2 [[maybe_unused]] = 12,
    MONSTER3 [[maybe_unused]] = 13,
    MONSTER4 [[maybe_unused]] = 14,
    MONSTER5 [[maybe_unused]] = 15,
    MONSTER7 [[maybe_unused]] = 16,
    MONSTER8 [[maybe_unused]] = 17,
    // NPC-bits
    NPC0 [[maybe_unused]]         = 18,
    NPC1 [[maybe_unused]]         = 19,
    NPC2 [[maybe_unused]]         = 20,
    NPC3 [[maybe_unused]]         = 21,
    NPC4 [[maybe_unused]]         = 22,
    NPC5 [[maybe_unused]]         = 23,
    LIGHT_YELLOW [[maybe_unused]] = 24,
    LIGHT_RED [[maybe_unused]]    = 25,
    LIGHT_WHITE [[maybe_unused]]  = 26,
    LIGHT_CIRCLE [[maybe_unused]] = 27,
    LIGHT_SQUARE [[maybe_unused]] = 28,
    LIGHT_SMALL [[maybe_unused]]  = 29,
    LIGHT_MEDIUM [[maybe_unused]] = 30,
    LIGHT_BIG [[maybe_unused]]    = 31
};
}