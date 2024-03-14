#include <algorithm>
#include <fstream>
#include <iostream>
#include <level/file.hpp>
#include <limits>
#include <stdexcept>

namespace Level {
void
writeLevelDataToFile(const std::string& filename, const typeLevelData& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Cant write to file");
    // Write header
    file.write(reinterpret_cast<const char*>(&data.Header), sizeof(data.Header));

    //Write assets
    const auto numAssets = data.Assets.Assets.size();
    file.write(reinterpret_cast<const char*>(&numAssets), sizeof(numAssets));

    for(const auto& asset : data.Assets.Assets){
        const auto assetNameLength = static_cast<uint8_t>(asset.size());
        file.write(reinterpret_cast<const char*>(&assetNameLength), sizeof(assetNameLength));   //Write length
        file.write(asset.c_str(), assetNameLength);
    }

    file.write(reinterpret_cast<const char*>(&data.Assets), sizeof(data.Assets));
    // Write tile-data
    /*
    const int size = data.Header.Level.SizeX * data.Header.Level.SizeY;
    for (int i = 0; i < size; i++) {
        file.write(reinterpret_cast<const char*>(data.Tiles[i]), sizeof(typeTileData));
    }
     */
    file.close();
}

typeLevelData*
readLevelData(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("Cant load file");
    typeHeader header = {};
    typeAssets asset  = {};
    file.read(reinterpret_cast<char*>(&header), sizeof(typeHeader));
    file.read(reinterpret_cast<char*>(&asset), sizeof(typeAssets));

    int  elements = header.Level.SizeX * header.Level.SizeY;
    auto tiles    = new typeTileData*[elements];
    for (int i = 0; i < elements; i++) {
        auto element = new typeTileData{};
        file.read(reinterpret_cast<char*>(element), sizeof(typeTileData));
        tiles[i] = element;
    }
    file.close();
    // All done, generate data
    auto level    = new typeLevelData;
    level->Header = header;
    level->Assets = asset;
    //level->Tiles  = tiles;

    return level;
}

void
removeAsset(const uint8_t& id, typeAssets& map) {
    //std::memset(map->Data[id].Asset, 0, sizeof(map->Data[id].Asset));
}

size_t
addAsset(const std::string& asset, typeAssets& map) {
    if(asset.empty())
        return -1;
    map.Assets.emplace_back(asset);
    return map.Assets.size();
}

std::optional<size_t>
findAsset(const std::string& asset, const typeAssets& map){
    auto it = std::find(map.Assets.begin(), map.Assets.end(), asset);
    if(it != map.Assets.end())
        return std::distance(map.Assets.begin(), it);
    return std::nullopt;
}

}