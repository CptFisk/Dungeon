#include <global.hpp>
#include <iostream>
#include <level/types/tile.hpp>

namespace Level::File {

void
readTileData(std::ifstream& file, typeTiles& data) {
    uint16_t readSize;

    file.read(reinterpret_cast<char*>(&readSize), sizeof(readSize));

    auto tiles = File::typeTiles(readSize);
    for (int i = 0; i < readSize; i++) {
        try {
            File::typeTileData tileData;
            file.read(reinterpret_cast<char*>(&tileData), sizeof(tileData.Type));
            uint8_t size;
            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            // Read base assets
            for (int j = 0; j < size; j++) {
                uint8_t id;
                file.read(reinterpret_cast<char*>(&id), sizeof(id));
                tileData.Base.emplace_back(id);
            }

            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            // Read overlays
            for (int j = 0; j < size; j++) {
                uint8_t id;
                file.read(reinterpret_cast<char*>(&id), sizeof(id));
                tileData.Top.emplace_back(id);
            }
            tiles.Tiles[i] = tileData;
        } catch (...) {
            std::cerr << "Error reading tiles" << std::endl;
        }
    }
    data = tiles;
}

void
writeTileData(std::ofstream& file, const typeTiles& data) {
    try {
        // Write normal tiles first
        file.write(reinterpret_cast<const char*>(&data.Size), sizeof(uint16_t));
        for (const auto& tile : data.Tiles) {
            // First we write the type
            file.write(reinterpret_cast<const char*>(&tile.Type), sizeof(tile.Type));
            // Write how big the array is
            const auto baseLength = UINT8(tile.Base.size());
            file.write(reinterpret_cast<const char*>(&baseLength), sizeof(baseLength));
            // Writing all base id:s
            for (const auto id : tile.Base)
                file.write(reinterpret_cast<const char*>(&id), sizeof(id));

            const auto overlayLength = UINT8(tile.Top.size());
            file.write(reinterpret_cast<const char*>(&overlayLength), sizeof(overlayLength));
            for (const auto id : tile.Top)
                file.write(reinterpret_cast<const char*>(&id), sizeof(id));
        }
    } catch (...) {
        std::cerr << "Error writing tiles" << std::endl;
    }
}

}