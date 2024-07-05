#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

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

size_t
addAsset(const std::string& asset, typeAssets& map); // Add a new item to the list, returns the id that was assigned

std::optional<size_t>
findAsset(const std::string& asset, const typeAssets& map); // Search for an asset, -1 if item don't exist

/**
 * @brief Function used to remove a asset both from the game-world but also from the visual map that you are editing.
 * @param assetName Name of the asset
 * @param map Asset list
 * @param fileTiles Reference to the fileData structure
 * @return True if a element was found and removed
 */
bool
removeAsset(const std::string& assetName, typeAssets& map);
}