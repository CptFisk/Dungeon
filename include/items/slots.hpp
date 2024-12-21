#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
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

NLOHMANN_JSON_SERIALIZE_ENUM(SlotType,
                             { { SlotType::Undefined, "Undefined" },
                               { SlotType::Amulet, "Amulet" },
                               { SlotType::Head, "Head" },
                               { SlotType::Chest, "Chest" },
                               { SlotType::Right, "Right" },
                               { SlotType::Left, "Left" },
                               { SlotType::Boots, "Boots" },
                               { SlotType::Bag, "Bag" },
                               { SlotType::Spell, "Spell" }})

}