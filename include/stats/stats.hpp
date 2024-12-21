#pragma once

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
};
}