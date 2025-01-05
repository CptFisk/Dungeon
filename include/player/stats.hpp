#pragma once
#include <stats/stats.hpp>

namespace Player {

class PlayerStats {
  public:
    PlayerStats(Stats::Stats& item);
    void incrementVitality();
    void incrementStamina();
    void incrementStrength();
    void incrementDexterity();
    void incrementIntelligence();
    void incrementLuck();

    Stats::Stats& getTotalStats();
  protected:
    double calculateHpGain();

  private:
    Stats::Stats  mPlayerStats; // Stats provided by leveling
    Stats::Stats& mItemStats;   // Reference to the stats calculated by items
    Stats::Stats  mTotal;       // The total added value of player stats and stats from items
};
}