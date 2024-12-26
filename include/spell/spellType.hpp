#pragma once
#include <nlohmann/json.hpp>
namespace Spells {

enum class School { Fire, Frost, Lightning };

NLOHMANN_JSON_SERIALIZE_ENUM(School, { { School::Fire, "Fire" }, { School::Frost, "Frost" }, { School::Lightning, "Lightning" } })

}