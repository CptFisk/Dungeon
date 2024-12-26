#pragma once
#include <nlohmann/json.hpp>

namespace Items {

enum class WeaponType { Staff, Axe, Sword, Bow, Shield };

NLOHMANN_JSON_SERIALIZE_ENUM(WeaponType,
                             { { WeaponType::Staff, "Staff" },
                               { WeaponType::Axe, "Axe" },
                               { WeaponType::Sword, "Sword" },
                               { WeaponType::Bow, "Bow" },
                               { WeaponType::Shield, "Shield" } })
}