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
    for (int i = 0; i < size; i++) {
        map[i] = new typeTileData{};
        map[i]->Id = UINT8_MAX;
    }
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
    std::memset(map->Data[id].Asset, 0, sizeof(map->Data[id].Asset));
}

uint8_t
addAsset(const char* asset, typeAssets* map) {
    if(strlen(asset) == 0)
        return UINT8_MAX;
    int position = 0;
    for(auto& item : map->Data){
        if(strlen(item.Asset) == 0){
            const auto length = strlen(asset);
            strncpy(item.Asset, asset, length);
            item.Asset[length] = '\0';
            return position;
        }
        position++;
    }
    return UINT8_MAX;
}

uint8_t
findAsset(const char* asset, typeAssets* map){
    int position = 0;
    for(const auto& item : map->Data){
        if(strcmp(item.Asset, asset) == 0)
            return position;
        position++;
    }
    return UINT8_MAX;
}

}