#include <global.hpp>
#include <iostream>
#include <level/types/tile.hpp>

namespace Level {

void
readTileData(std::ifstream& file, typeTiles& data) {
    for (int i = 0; i < MAP_SIZE; i++) {
        try {
            typeTileData tileData;
            uint32_t type;
            file.read(reinterpret_cast<char*>(&type), sizeof(uint32_t));
            tileData.Type = type;
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
            data.Tiles[i] = tileData;
        } catch (...) {
            std::cerr << "Error reading tiles" << std::endl;
        }
    }
}

void
writeTileData(std::ofstream& file, const typeTiles& data) {
    try {
        for (const auto& tile : data.Tiles) {
            auto type = static_cast<uint32_t>(tile.Type.to_ulong());
            // First we write the type
            file.write(reinterpret_cast<const char*>(&type), sizeof(type));
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