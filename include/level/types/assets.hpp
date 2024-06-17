#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace Level::File {

struct typeAssets {
    uint8_t                  AnimationValue; // Used to calculate the numbers of segments we need
    std::vector<std::string> Assets;         // Asset names
};

void
readAssets(std::ifstream& file, typeAssets& data);

void
writeAssets(std::ofstream& file, const typeAssets& data);

}