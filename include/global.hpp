#pragma once
#include <cstdint>
#include <random>
#include <SDL.h>

// Casting macros
#define UINT8(x)        static_cast<uint8_t>(x)
#define UINT16(x)       static_cast<uint16_t>(x)
#define FLOAT(x)        static_cast<float>(x)
#define INT(x)          static_cast<int>(x)
#define UINT8_STRING(x) std::to_string(static_cast<int>(x))
#define STRING_UINT8(x) static_cast<uint8_t>(std::stoi(x))

//Default font
const std::string DEFAULT_FONT("8bit16");
const SDL_Colour LIGHT_FONT{ 224, 224, 224, 255 };
// Map size
[[maybe_unused]] const int     MAP_WIDTH     = 128;
[[maybe_unused]] const int     SEGMENT_SIZE  = 128;
[[maybe_unused]] constexpr int MAP_SIZE      = MAP_WIDTH * MAP_WIDTH;
[[maybe_unused]] const int     BLOCKS_WIDTH  = 24;  //Number of squares in x-direction
[[maybe_unused]] const int     BLOCKS_HEIGHT = 18;  //Number of squares in y-direction
[[maybe_unused]] const int     PIXEL_SIZE    = 16;  //Size of each block

#pragma region Bitmask
[[maybe_unused]] const int LIGHT_ANIMATION_FRAMES = 7; // Constant for how many frames a light-effect exist of

[[maybe_unused]] const unsigned long int LIGHT_BITS   = 0xFF000000; // Used to mask out bit 24-31
[[maybe_unused]] const unsigned long int LIGHT_COLOUR = 0x7000000;
[[maybe_unused]] const unsigned long int LIGHT_SHAPE  = 0x18000000;
[[maybe_unused]] const unsigned long int LIGHT_SIZE   = 0xE0000000;

[[maybe_unused]] const unsigned long int MONSTER_BITS = 0x3FC00;  // Bitmask for monsters
[[maybe_unused]] const unsigned long int NPC_BITS     = 0xFC0000; // Bitmask for NPC:s

[[maybe_unused]] const unsigned long int WALL_OBSTACLE     = 0xC; // Walls and obstacle
[[maybe_unused]] const unsigned long int WALL_OBSTACLE_NPC = 0x4C;
#pragma endregion

enum Orientation : uint8_t {
    North                      = 1 << 0,
    East                       = 1 << 1,
    South                      = 1 << 2,
    West                       = 1 << 3,
    NorthEast [[maybe_unused]] = North | East,
    NorthWest [[maybe_unused]] = North | West,
    SouthEast [[maybe_unused]] = South | East,
    SouthWest [[maybe_unused]] = South | West,
    All [[maybe_unused]]       = North | East | South | West
};

enum Direction : uint8_t { Forward = 1 << 0, Backward = 1 << 1, Right = 1 << 2, Left = 1 << 3 };

/**
 * @brief Different game-modes, used to handle inputs and other actions
 */
enum class GameMode { Menu, Game, Inventory, Attributes };

/**
 * @brief Returns a random direction
 * @return Type as enum
 */
inline Orientation
getRandomDirection() {
    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dist(0, 3);

    switch (dist(gen)) {
        case 0:
            return North;
        case 1:
            return West;
        case 2:
            return South;
        case 3:
            return East;
    }

    return North;
}