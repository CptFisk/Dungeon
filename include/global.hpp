#pragma once
#include <cstdint>

// Casting macros
#define UINT8(x) static_cast<uint8_t>(x)
#define FLOAT(x) static_cast<uint8_t>(x)
#define INT(x)   static_cast<int>(x)
enum Directions : uint8_t { NORTH = 1 << 0, EAST = 1 << 1, SOUTH = 1 << 2, WEST = 1 << 3, ALL = NORTH | EAST | SOUTH | WEST };