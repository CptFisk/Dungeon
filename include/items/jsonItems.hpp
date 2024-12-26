#pragma once
#include <items/slots.hpp>
#include <items/weaponType.hpp>
#include <nlohmann/json.hpp>
#include <optional>
#include <stats/stats.hpp>
#include <string>

namespace Items {

struct typeItemJSON {
    int                       Id;
    std::string               Graphic;
    std::string               Description;
    SlotType                  Slot;
    std::optional<WeaponType> Weapon;   //Optional, only used if Slot = Left or Right
    Stats::Stats              Stats;
};

inline void
to_json(nlohmann::json& nlohmann_json_j, const typeItemJSON& nlohmann_json_t) {
    nlohmann_json_j["Id"]          = nlohmann_json_t.Id;
    nlohmann_json_j["Graphic"]     = nlohmann_json_t.Graphic;
    nlohmann_json_j["Description"] = nlohmann_json_t.Description;
    nlohmann_json_j["Slot"]        = nlohmann_json_t.Slot;
    nlohmann_json_j["Stats"]       = nlohmann_json_t.Stats;
}
inline void
from_json(const nlohmann::json& nlohmann_json_j, typeItemJSON& nlohmann_json_t) {
    nlohmann_json_j.at("Id").get_to(nlohmann_json_t.Id);
    nlohmann_json_j.at("Graphic").get_to(nlohmann_json_t.Graphic);
    if (nlohmann_json_j.contains("Description")) {
        nlohmann_json_t.Description = nlohmann_json_j.at("Description").get<std::string>();
    } else {
        nlohmann_json_t.Description = "";
    }
    if (nlohmann_json_j.contains("Weapon")) {
        nlohmann_json_t.Weapon = nlohmann_json_j.at("Weapon").get<WeaponType>();
    } else {
        nlohmann_json_t.Weapon = std::nullopt;
    }
    nlohmann_json_j.at("Description").get_to(nlohmann_json_t.Description);
    nlohmann_json_j.at("Slot").get_to(nlohmann_json_t.Slot);
    nlohmann_json_j.at("Stats").get_to(nlohmann_json_t.Stats);
}

}