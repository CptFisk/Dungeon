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

/**
 * @brief Read assets from a filestream
 */
void
readAssetData(std::ifstream& file, typeAssets& data);

/**
 * @brief Write assets to a filestream
 */
void
writeAssetData(std::ofstream& file, const typeAssets& data);

}