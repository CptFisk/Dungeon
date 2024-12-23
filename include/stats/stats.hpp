#pragma once
#include <nlohmann/json.hpp>

namespace Stats {

struct Stats {
    int Vitality;     // Determines the player health
    int Stamina;      // Stamina
    int Strength;     // Determines the strength
    int Dexterity;    // Dexterity
    int Intelligence; // Improves casting
    int Luck;         // Random parameters

    // Basic constructor
    Stats()
      : Vitality(0)
      , Stamina(0)
      , Strength(0)
      , Dexterity(0)
      , Intelligence(0)
      , Luck(0) {}

    Stats(const int& vit, const int& stamina, const int& str, const int& dex, const int& intelligence, const int& luck)
      : Vitality(vit)
      , Stamina(stamina)
      , Strength(str)
      , Dexterity(dex)
      , Intelligence(intelligence)
      , Luck(luck) {};

    // Addition operator overload
    Stats operator+(const Stats& a) const {
        return Stats(a.Vitality + Vitality,
                     a.Stamina + Stamina,
                     a.Strength + Strength,
                     a.Dexterity + Dexterity,
                     a.Intelligence + Intelligence,
                     a.Luck + Luck);
    };

    // Addition operator overload
    Stats operator-(const Stats& a) const {
        return Stats(Vitality - a.Vitality,
                     Stamina - a.Stamina,
                     Strength - Strength,
                     Dexterity - Dexterity,
                     Intelligence - Intelligence,
                     Luck - Luck);
    };
};

inline void
to_json(nlohmann::json& nlohmann_json_j, const Stats& nlohmann_json_t) {
    nlohmann_json_j["Vitality"]     = nlohmann_json_t.Vitality;
    nlohmann_json_j["Stamina"]      = nlohmann_json_t.Stamina;
    nlohmann_json_j["Strength"]     = nlohmann_json_t.Strength;
    nlohmann_json_j["Dexterity"]    = nlohmann_json_t.Dexterity;
    nlohmann_json_j["Intelligence"] = nlohmann_json_t.Intelligence;
    nlohmann_json_j["Luck"]         = nlohmann_json_t.Luck;
}

inline void
from_json(const nlohmann::json& nlohmann_json_j, Stats& nlohmann_json_t) {
    // Vitality
    if (nlohmann_json_j.contains("Vitality")) {
        nlohmann_json_t.Vitality = nlohmann_json_j.at("Vitality").get<int>();
    } else {
        nlohmann_json_t.Vitality = 0;
    }
    // Stamina
    if (nlohmann_json_j.contains("Stamina")) {
        nlohmann_json_t.Stamina = nlohmann_json_j.at("Stamina").get<int>();
    } else {
        nlohmann_json_t.Stamina = 0;
    }
    // Strength
    if (nlohmann_json_j.contains("Strength")) {
        nlohmann_json_t.Strength = nlohmann_json_j.at("Strength").get<int>();
    } else {
        nlohmann_json_t.Strength = 0;
    }
    // Dexterity
    if (nlohmann_json_j.contains("Dexterity")) {
        nlohmann_json_t.Dexterity = nlohmann_json_j.at("Dexterity").get<int>();
    } else {
        nlohmann_json_t.Dexterity = 0;
    }
    // Intelligence
    if (nlohmann_json_j.contains("Intelligence")) {
        nlohmann_json_t.Intelligence = nlohmann_json_j.at("Intelligence").get<int>();
    } else {
        nlohmann_json_t.Intelligence = 0;
    }
    // Luck
    if (nlohmann_json_j.contains("Luck")) {
        nlohmann_json_t.Luck = nlohmann_json_j.at("Luck").get<int>();
    } else {
        nlohmann_json_t.Luck = 0;
    }
}
}