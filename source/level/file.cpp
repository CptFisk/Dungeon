#include <algorithm>
#include <fstream>
#include <iostream>
#include <level/file.hpp>
#include <limits>
#include <stdexcept>

namespace Level::File {
void
writeLevelDataToFile(const std::string& filename, const typeLevelData& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Cant write to file");
    // Write header
    file.write(reinterpret_cast<const char*>(&data.Header), sizeof(data.Header));

    // Write assets
    const auto numAssets = data.Assets.Assets.size();
    file.write(reinterpret_cast<const char*>(&numAssets), sizeof(numAssets));

    for (const auto& asset : data.Assets.Assets) {
        const auto assetNameLength = static_cast<uint8_t>(asset.size());
        file.write(reinterpret_cast<const char*>(&assetNameLength), sizeof(assetNameLength)); // Write length
        file.write(asset.c_str(), assetNameLength);
    }

    // The tricky part, save tile data
    file.write(reinterpret_cast<const char*>(&data.Tiles.Size), sizeof(data.Tiles.Size));

    for (const auto& tile : data.Tiles.Tiles) {
        // First we write the type
        file.write(reinterpret_cast<const char*>(&tile.Type), sizeof(tile.Type));
        // Write how big the array is
        const auto idLength = static_cast<uint8_t>(tile.Id.size());
        file.write(reinterpret_cast<const char*>(&idLength), sizeof(idLength));
        // Writing all ID:s
        for (const auto id : tile.Id)
            file.write(reinterpret_cast<const char*>(&id), sizeof(id));
    }
    file.close();
}

Level::File::typeLevelData
readLevelData(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("Cant load file");
    typeHeader header = {};
    typeAssets assets;
    // Read size, nothing special here
    file.read(reinterpret_cast<char*>(&header), sizeof(typeHeader));
    // Read the size of how many assets is stored in the file
    size_t numberOfAssets;
    file.read(reinterpret_cast<char*>(&numberOfAssets), sizeof(numberOfAssets));
    for (int i = 0; i < numberOfAssets; i++) {
        uint8_t assetLength = {};
        file.read(reinterpret_cast<char*>(&assetLength), sizeof(assetLength));
        char* assetName = new char[assetLength + 1]{};
        file.read(assetName, assetLength);
        assets.Assets.emplace_back(assetName);
        delete[] assetName; // Clear memory
    }

    uint16_t tileSize;
    file.read(reinterpret_cast<char*>(&tileSize), sizeof(tileSize));

    auto tiles = File::typeTiles(tileSize);
    for (int i = 0; i < tileSize; i++) {
        File::typeTileData tileData;
        file.read(reinterpret_cast<char*>(&tileData), sizeof(tileData.Type));
        uint8_t idSize;
        file.read(reinterpret_cast<char*>(&idSize), sizeof(idSize));
        for (int j = 0; j < idSize; j++) {
            uint8_t id;
            file.read(reinterpret_cast<char*>(&id), sizeof(id));
            tileData.Id.emplace_back(id);
        }
        tiles.Tiles[i] = tileData;
    }
    file.close();
    // Generating response
    auto data = typeLevelData(tileSize);
    return data;
}

size_t
addAsset(const std::string& asset, typeAssets& map) {
    if (asset.empty())
        return -1;
    map.Assets.emplace_back(asset);
    return map.Assets.size();
}

std::optional<size_t>
findAsset(const std::string& asset, const typeAssets& map) {
    auto it = std::find(map.Assets.begin(), map.Assets.end(), asset);
    if (it != map.Assets.end())
        return std::distance(map.Assets.begin(), it);
    return std::nullopt;
}

}