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
        file.write(reinterpret_cast<const char*>(data.Tiles[i]), sizeof(Tile));
    }
    file.close();
}

typeLevel*
loadLevelFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("Cant load file");
    Header header = {};
    Assets asset  = {};
    file.read(reinterpret_cast<char*>(&header), sizeof(Header));
    file.read(reinterpret_cast<char*>(&asset), sizeof(Assets));
    // Determine size of tiles
    file.seekg(0, std::ios::end);
    std::streampos headerSize = sizeof(Header);
    std::streampos assetSize  = sizeof(Assets);

    auto remaining = file.tellg();
    auto data = remaining - headerSize - assetSize; // Calculate size

    file.seekg(headerSize + assetSize, std::ios::beg);
    int elements = header.MapSizeX * header.MapSizeY;
    Tile** tiles = new Tile*[elements];
    for(int i = 0; i < elements; i++){
        Tile* element = new Tile{};
        file.read(reinterpret_cast<char*>(element), sizeof(Tile));
        tiles[i] = element;
    }

    //All done, generate data
    auto level = new typeLevel;
    level->Header = header;
    level->Assets = asset;
    level->Tiles = tiles;

    return level;
}

Tile**
newTile(const int& x, const int& y) {
    const int size = x * y;
    Tile**    map  = new Tile*[x * y];
    for (int i = 0; i < size; i++)
        map[i] = new Tile{};
    return map;
}

void
deleteTile(Tile** tile, const int& elements) {
    for (int i = 0; i < elements; i++)
        delete tile[i];
    delete[] tile;
}

void
removeAsset(const uint8_t& id, Assets* map) {
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
        memset(&map->Data[MAP_META_MAX - 1], 0, sizeof(Asset));
    }
}

bool
addAsset(const char* asset, Assets* map) {
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