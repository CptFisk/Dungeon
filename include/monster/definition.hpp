#pragma once
#include <array>
#include <string>

namespace Monster {

struct MonsterData {
    std::string Name;
    std::string DefaultImage;
};

enum class Type { SLIME = 1, CAVE_CRAWLER = 2 };

const std::array<MonsterData, 3> monsters = { {
  { "", "" },                            // Default blank
  { "Slime", "Slime" },                  // Slime
  { "Cave Crawler", "CaveCrawlerSouth" } // Cave Crawler
} };

}