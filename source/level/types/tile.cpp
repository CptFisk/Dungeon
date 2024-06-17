#include <level/types/tile.hpp>
#include <iostream>
#include <global.hpp>

namespace Level::File{

void
readTileData(std::ifstream& file, typeTiles& data){
    uint16_t readSize;

    file.read(reinterpret_cast<char*>(&readSize), sizeof(readSize));

    auto tiles = File::typeTiles(readSize);
    for (int i = 0; i < readSize; i++) {
        try {
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
        }catch(...){
            std::cerr << "Error reading tiles" << std::endl;
        }
    }
    data = tiles;
}

void
writeTileData(std::ofstream& file, const typeTiles& data){
    //Write the size first
    file.write(reinterpret_cast<const char*>(&data.Size), sizeof(uint16_t));

    for (const auto& tile : data.Tiles) {
        try {
            // First we write the type
            file.write(reinterpret_cast<const char*>(&tile.Type), sizeof(tile.Type));
            // Write how big the array is
            const auto idLength = static_cast<uint8_t>(tile.Id.size());
            file.write(reinterpret_cast<const char*>(&idLength), sizeof(idLength));
            // Writing all ID:s
            for (const auto id : tile.Id)
                file.write(reinterpret_cast<const char*>(&id), sizeof(id));
        }catch(...){
            std::cerr << "Error writing tiles" << std::endl;
        }
    }
}

}