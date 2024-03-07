#include <cstring>
#include <fstream>
#include <iostream>
#include <level/structures.hpp>
#include <stdexcept>

namespace Level {
void
writeLevelDataToFile(const std::string& filename, const typeLevelData& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Cant write to file");
    // Write header
    file.write(reinterpret_cast<const char*>(&data.Header), sizeof(data.Header));
    // Write meta
    file.write(reinterpret_cast<const char*>(&data.Assets), sizeof(data.Assets));
    // Write tile-data
    const int size = data.Header.Level.SizeX * data.Header.Level.SizeY;
    for (int i = 0; i < size; i++) {
        file.write(reinterpret_cast<const char*>(data.Tiles[i]), sizeof(typeTileData));
    }
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
    level->Tiles  = tiles;

    return level;
}

typeTileData**
newTileData(const int& x, const int& y) {
    const int size = x * y;
    auto      map  = new typeTileData*[x * y];
    for (int i = 0; i < size; i++)
        map[i] = new typeTileData{};
    return map;
}

void
deleteTile(typeTileData** tile, const int& elements) {
    for (int i = 0; i < elements; i++)
        delete tile[i];
    delete[] tile;
}

void
deleteTile(typeTile** tile, const int& elements) {
    for (int i = 0; i < elements; i++)
        delete tile[i];
    delete[] tile;
}

void
removeAsset(const uint8_t& id, typeAssets* map) {
    bool found = false;
    for (int i = 0; i < TEXT_MAX_LENGTH; i++) {
        if (found) {
            map->Data[i - 1] = map->Data[i];
        } else if (map->Data[i].Id == id) {
            found = true;
        }
    }
    if (found) {
        // Clear the last element (optional)
        memset(&map->Data[TEXT_MAX_LENGTH - 1], 0, sizeof(typeAssetItem));
    }
}

int
addAsset(const char* asset, typeAssets* map) {
    if(strlen(asset) == 0)
        return false;
    int lowest = 0;
    for (auto& item : map->Data) {
        if (item.Id == 0) {
            item.Id  = ++lowest;
            auto len = strlen(asset);
            strncpy(item.Asset, asset, len);
            item.Asset[len] = '\0';
            return item.Id;
        } else {
            if (item.Id > lowest)
                lowest = item.Id;
        }
    }
    return -1;
}

int
existAsset(const char* asset, typeAssets* map){
    for(const auto& item : map->Data){
        if(strcmp(item.Asset, asset) == 0)
            return item.Id;
    }
    return -1;
}

}