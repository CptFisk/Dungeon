#include <algorithm>
#include <fstream>
#include <global.hpp>
#include <iostream>
#include <level/file.hpp>
#include <stdexcept>

namespace Level::File {

void
writeLevelDataToFile(const std::string& filename, const typeLevelData& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Cant write to file");
    // Write header
    file.write(reinterpret_cast<const char*>(&data.Header), sizeof(data.Header));

    // Write the biggest animated value that we have
    file.write(reinterpret_cast<const char*>(&data.Assets.AnimationValue), sizeof(data.Assets.AnimationValue));

    writeAssetData(file, data.Assets);
    writeTileData(file, data.Tiles);
    writeDoorData(file, data.Doors);
    writeWarpData(file, data.Warps);

    file.close();
}

Level::File::typeLevelData
readLevelData(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("Cant load file");
    typeHeader                 header = {};
    typeAssets                 assets;
    typeTiles                  tiles = {};
    std::vector<typeDoorsData> doors;
    std::vector<typeWarpData>  warps;
    uint16_t                   readSize; // Used to store sizes of objects
    // Read size, nothing special here
    file.read(reinterpret_cast<char*>(&header), sizeof(typeHeader));

    file.read(reinterpret_cast<char*>(&assets.AnimationValue), sizeof(assets.AnimationValue));

    // Read the size of how many assets is stored in the file
    readAssetData(file, assets);
    readTileData(file, tiles);
    readDoorData(file, doors);
    readWarpData(file, warps);

    file.close();
    // Generating response
    return typeLevelData{ header, assets, tiles, doors, warps, typeSpawn() };
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

bool
removeAsset(const std::string& assetName, typeAssets& map, Level::File::typeTiles& fileTiles) {
    // Calculate our id
    int  assetId;
    bool found = false;
    for (auto it = map.Assets.begin(); it != map.Assets.end(); ++it) {
        if (*it == assetName) {
            assetId = static_cast<int>(std::distance(map.Assets.begin(), it));
            map.Assets.erase(it);
            found = true;
            break; // Stop the loop
        }
    }
    if (!found)
        return false;

    // The asset was found, and we know the ID. Now we have to remove it from the
    for (auto& tile : fileTiles.Tiles) {
        // Loop all the different id's that exist
        for (auto it = tile.Id.begin(); it != tile.Id.end();) {
            if (*it == assetId) {
                it = tile.Id.erase(it);
            } else if (*it > assetId) {
                --(*it);
                ++it;
            } else {
                ++it;
            }
        }
    }
    return true;
}

}