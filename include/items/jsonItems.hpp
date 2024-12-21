#pragma once
#include <items/slots.hpp>
#include <nlohmann/json.hpp>
#include <stats/stats.hpp>
#include <string>
namespace Items {

struct typeItemJSON {
    int          Id;
    std::string  Graphic;
    SlotType     Slot;
    Stats::Stats Stats;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeItemJSON , Id, Graphic, Slot, Stats)


}