#pragma once
#include <cstdint>

namespace Items {
enum class SlotType {
    Undefined, // Not defined
    Amulet,    // Amulet slot
    Head,      // Head slot
    Chest,     // Chest slot
    Right,
    Left,
    Boots, // Boots slot
    Bag,   // Might be set later
    Spell
};

}