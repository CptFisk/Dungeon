#pragma once
#include <cstdint>
#include <random>

// Casting macros
#define UINT8(x)        static_cast<uint8_t>(x)
#define UINT16(x)       static_cast<uint16_t>(x)
#define FLOAT(x)        static_cast<float>(x)
#define INT(x)          static_cast<int>(x)
#define UINT8_STRING(x) std::to_string(static_cast<int>(x))
#define STRING_UINT8(x) static_cast<uint8_t>(std::stoi(x))

// Map size
[[maybe_unused]] const int     MAP_WIDTH    = 128;
[[maybe_unused]] const int     SEGMENT_SIZE = 128;
[[maybe_unused]] constexpr int MAP_SIZE     = MAP_WIDTH * MAP_WIDTH;

#pragma region Bitmask
[[maybe_unused]] const int LIGHT_ANIMATION_FRAMES = 7; // Constant for how many frames a light-effect exist of

[[maybe_unused]] const unsigned long int LIGHT_BITS   = 0xFF000000; // Used to mask out bit 24-31
[[maybe_unused]] const unsigned long int LIGHT_COLOUR = 0x7000000;
[[maybe_unused]] const unsigned long int LIGHT_SHAPE  = 0x18000000;
[[maybe_unused]] const unsigned long int LIGHT_SIZE   = 0xE0000000;

[[maybe_unused]] const unsigned long int MONSTER_BITS = 0x3FC00;  // Bitmask for monsters
[[maybe_unused]] const unsigned long int NPC_BITS     = 0xFC0000; // Bitmask for NPC:s

[[maybe_unused]] const unsigned long int WALL_OBSTACLE = 0xC;   //Walls and obstacle
[[maybe_unused]] const unsigned long int WALL_OBSTACLE_NPC = 0x4C;
#pragma endregion

enum Directions : uint8_t {
    NORTH                       = 1 << 0,
    EAST                        = 1 << 1,
    SOUTH                       = 1 << 2,
    WEST                        = 1 << 3,
    NORTH_EAST [[maybe_unused]] = NORTH | EAST,
    NORTH_WEST [[maybe_unused]] = NORTH | WEST,
    SOUTH_EAST [[maybe_unused]] = SOUTH | EAST,
    SOUTH_WEST [[maybe_unused]] = SOUTH | WEST,
    ALL [[maybe_unused]]        = NORTH | EAST | SOUTH | WEST
};

/**
 * @brief Returns a random direction
 * @return Type as enum
 */
inline Directions
getRandomDirection() {
    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dist(0, 3);

    switch (dist(gen)) {
        case 0:
            return NORTH;
        case 1:
            return WEST;
        case 2:
            return SOUTH;
        case 3:
            return EAST;
    }

    return NORTH;
}