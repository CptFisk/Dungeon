#pragma once
#include <vector>
#include <string>
#include <cstdint>

namespace Level::File {

struct typeAssets {
    uint8_t AnimationValue;  //Used to calculate the numbers of segments we need
    std::vector<std::string> Assets; // Asset names
};

}