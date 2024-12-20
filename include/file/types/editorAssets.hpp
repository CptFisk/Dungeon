#pragma once
#include <cstdint>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace File {

struct typeAssets {
    uint8_t                  AnimationValueBase; // Used to calculate the numbers of segments we need
    uint8_t                  AnimationValueTop;  // Used to calculate the numbers of segments we need
    std::vector<std::string> Assets;             // Asset names
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

size_t
addAsset(const std::string& asset, typeAssets& map); // Add a new item to the list, returns the id that was assigned

std::optional<size_t>
findAsset(const std::string& asset, const typeAssets& map); // Search for an asset, -1 if item don't exist

}