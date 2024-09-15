#include <algorithm>
#include <global.hpp>
#include <iostream>
#include <file/types/editorAssets.hpp>

namespace File {

void
readAssetData(std::ifstream& file, typeAssets& data) {
    file.read(reinterpret_cast<char*>(&data.AnimationValueBase), sizeof(data.AnimationValueBase));
    file.read(reinterpret_cast<char*>(&data.AnimationValueTop), sizeof(data.AnimationValueTop));
    uint16_t readSize;
    file.read(reinterpret_cast<char*>(&readSize), sizeof(readSize));

    for (uint16_t i = 0; i < readSize; i++) {
        try {
            uint8_t assetLength = {};
            file.read(reinterpret_cast<char*>(&assetLength), sizeof(assetLength));
            char* assetName = new char[assetLength + 1]{};
            file.read(assetName, assetLength);
            data.Assets.emplace_back(assetName);
            delete[] assetName; // Clear memory
        } catch (...) {
            std::cerr << "Error reading assets" << std::endl;
        }
    }
}

void
writeAssetData(std::ofstream& file, const typeAssets& data) {
    // Write the biggest animated value that we have
    file.write(reinterpret_cast<const char*>(&data.AnimationValueBase), sizeof(data.AnimationValueBase));
    file.write(reinterpret_cast<const char*>(&data.AnimationValueTop), sizeof(data.AnimationValueTop));
    // Get the number os assets in map and store it as uint16_t
    const auto numAssets = UINT16(data.Assets.size());
    file.write(reinterpret_cast<const char*>(&numAssets), sizeof(uint16_t));

    for (const auto& asset : data.Assets) {
        try {
            const auto assetNameLength = static_cast<uint8_t>(asset.size());
            file.write(reinterpret_cast<const char*>(&assetNameLength), sizeof(assetNameLength)); // Write length
            file.write(asset.c_str(), assetNameLength);
        } catch (...) {
            std::cerr << "Error writing assets" << std::endl;
        }
    }
}

size_t
addAsset(const std::string& asset, typeAssets& map) {
    const auto size = map.Assets.size();
    map.Assets.emplace_back(asset);
    return size;
}

std::optional<size_t>
findAsset(const std::string& asset, const typeAssets& map) {
    auto it = std::find(map.Assets.begin(), map.Assets.end(), asset);
    if (it != map.Assets.end())
        return std::distance(map.Assets.begin(), it);
    return std::nullopt;
}


}