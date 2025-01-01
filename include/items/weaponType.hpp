#pragma once
#include <nlohmann/json.hpp>

namespace Items {

enum class WeaponType { None, Staff, Axe, Sword, Bow, Shield };

NLOHMANN_JSON_SERIALIZE_ENUM(WeaponType,
                             { { WeaponType::None, "None" },
                               { WeaponType::Staff, "Staff" },
                               { WeaponType::Axe, "Axe" },
                               { WeaponType::Sword, "Sword" },
                               { WeaponType::Bow, "Bow" },
                               { WeaponType::Shield, "Shield" } })
}