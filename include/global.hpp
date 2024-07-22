#pragma once
#include <cstdint>

// Casting macros
#define UINT8(x)        static_cast<uint8_t>(x)
#define UINT16(x)       static_cast<uint16_t>(x)
#define FLOAT(x)        static_cast<float>(x)
#define INT(x)          static_cast<int>(x)
#define UINT8_STRING(x) std::to_string(static_cast<int>(x))
#define STRING_UINT8(x) static_cast<uint8_t>(std::stoi(x))

// Map size
const int     MAP_WIDTH = 128;
constexpr int MAP_SIZE  = MAP_WIDTH * MAP_WIDTH;

const int               LIGHT_ANIMATION_FRAMES = 7;          // Constant for how many frames a light-effect exist of
const unsigned long int LIGHT_BITS             = 0xFF000000; // Used to mask out bit 24-31
const unsigned long int LIGHT_CIRCLE = 0x0;
const unsigned long int LIGHT_SQUARE = 0x0;

const unsigned long int LIGHT_RED = 0x0;
const unsigned long int LIGHT_YELLOW = 0x0;
const unsigned long int LIGHT_WHITE = 0x0;

const unsigned long int LIGHT_SMALL = 0x0;
const unsigned long int LIGHT_MEDIUM = 0x0;
const unsigned long int LIGHT_BIG = 0x0;


enum Directions : uint8_t { NORTH = 1 << 0, EAST = 1 << 1, SOUTH = 1 << 2, WEST = 1 << 3, ALL = NORTH | EAST | SOUTH | WEST };