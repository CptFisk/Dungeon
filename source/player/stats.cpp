#include <player/stats.hpp>
#include <cmath>


namespace Player {

PlayerStats::PlayerStats(Stats::Stats& item)
  : mItemStats(item) {}

Stats::Stats&
PlayerStats::getTotalStats() {
    return mTotal;
}

double
PlayerStats::calculateHpGain(){
    return std::log(mTotal.Vitality + M_E);
}
}