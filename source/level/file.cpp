#include <algorithm>
#include <fstream>
#include <iostream>
#include <level/file.hpp>
#include <level/types/header.hpp>
#include <stdexcept>

namespace Level::File {

void
writeLevelDataToFile(const std::string& filename, const typeLevelData& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Cant write to file");
    // Write header
    writeHeaderData(file, data.Header);
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
        throw std::runtime_error("Cant load file: " + filename);
    typeHeaderData             header = {};
    typeAssets                 assets;
    typeTiles                  tiles = {};
    std::vector<typeDoorsData> doors;
    std::vector<typeWarpData>  warps;

    // Read the size of how many assets is stored in the file
    readHeaderData(file, header);
    readAssetData(file, assets);
    readTileData(file, tiles);
    readDoorData(file, doors);
    readWarpData(file, warps);

    file.close();
    // Generating response
    return typeLevelData{ header, assets, tiles, doors, warps, typeSpawn() };
}

}