#include <cstring>
#include <fstream>
#include <level/structures.hpp>
#include <stdexcept>
#include <iostream>

namespace Level {
void
writeLevelToFile(const std::string& filename, const typeLevel& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Cant write to file");
    // Write header
    file.write(reinterpret_cast<const char*>(&data.Header), sizeof(data.Header));
    // Write meta
    file.write(reinterpret_cast<const char*>(&data.Assets), sizeof(data.Assets));
    // Write tile-data
    const int size = data.Header.MapSizeX * data.Header.MapSizeY;
    for (int i = 0; i < size; i++) {
        file.write(reinterpret_cast<const char*>(data.Tiles[i]), sizeof(typeTile));
    }
    file.close();
}

typeLevel*
loadLevelFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("Cant load file");
    typeHeader header = {};
    typeAssets asset  = {};
    file.read(reinterpret_cast<char*>(&header), sizeof(typeHeader));
    file.read(reinterpret_cast<char*>(&asset), sizeof(typeAssets));
    // Determine size of tiles
    file.seekg(0, std::ios::end);
    std::streampos headerSize = sizeof(typeHeader);
    std::streampos assetSize  = sizeof(typeAssets);

    auto remaining = file.tellg();
    auto data = remaining - headerSize - assetSize; // Calculate size

    file.seekg(headerSize + assetSize, std::ios::beg);
    int elements = header.MapSizeX * header.MapSizeY;
    typeTile** tiles = new typeTile*[elements];
    for(int i = 0; i < elements; i++){
        typeTile* element = new typeTile{};
        file.read(reinterpret_cast<char*>(element), sizeof(typeTile));
        tiles[i] = element;
    }

    //All done, generate data
    auto level = new typeLevel;
    level->Header = header;
    level->Assets = asset;
    level->Tiles = tiles;

    return level;
}

typeTile**
newTile(const int& x, const int& y) {
    const int size = x * y;
    typeTile**    map  = new typeTile*[x * y];
    for (int i = 0; i < size; i++)
        map[i] = new typeTile{};
    return map;
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
    for (int i = 0; i < MAP_META_MAX; i++) {
        if (found) {
            map->Data[i - 1] = map->Data[i];
        } else if (map->Data[i].Id == id) {
            found = true;
        }
    }
    if (found) {
        // Clear the last element (optional)
        memset(&map->Data[MAP_META_MAX - 1], 0, sizeof(typeAssetItem));
    }
}

bool
addAsset(const char* asset, typeAssets* map) {
    int lowest = 0;
    for (int i = 0; i < MAP_META_MAX; i++) {
        if (map->Data[i].Id == 0) {
            map->Data[i].Id = ++lowest;
            auto len        = strlen(asset);
            strncpy(map->Data[i].Asset, asset, len);
            map->Data[i].Asset[len] = '\0'; // Null-terminate
            return true;
        } else {
            if (map->Data[i].Id > lowest)
                lowest = map->Data[i].Id;
        }
    }
    return false;
}
}