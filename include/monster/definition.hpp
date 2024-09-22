#pragma once
#include <array>
#include <string>

namespace Monster {

struct MonsterData {
    std::string Name;
    std::string DefaultImage;
};

enum class Type {
    SPARE1       = 1, // Spare
    CAVE_CRAWLER = 2, // Cave crawler
    SLIME_BLUE   = 3, // Blue small slime
    SLIME_GREEN  = 4, // Green small slime
    SLIME_PURPLE = 5, // Purple small slime
    SLIME_RED    = 6, // Red small slime
    BEAN_MAN     = 7  // Green bean man
};

const std::array<MonsterData, 8> monsters = { { { "", "" },                             // Default blank
                                                { "SPARE1", "SPARE" },                  // Slime
                                                { "Cave Crawler", "CaveCrawlerSouth" }, // Cave Crawler
                                                { "Slime blue", "SlimeBlueSouth" },     // Blue slime
                                                { "Slime green", "SlimeGreenSouth" },   // Green slime
                                                { "Slime purple", "SlimePurpleSouth" }, // Purple slime
                                                { "Slime red", "SlimeRedSouth" },       // Red slime
                                                { "Bean man", "BeanManSouth" } } };

}