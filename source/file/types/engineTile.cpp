#include <file/types/engineTile.hpp>
#include <iostream>
#include <error.hpp>
namespace File {

void
readEngineTileData(std::ifstream& file, std::vector<std::bitset<32>>& data) {
    uint16_t size = {};
    file.read(reinterpret_cast<char*>(&size), sizeof(uint16_t));
    ASSERT_WITH_MESSAGE(size == 0, "Size cant be read")
    for(int i = 0; i < size; i++){
        uint32_t type;
        file.read(reinterpret_cast<char*>(&type), sizeof(uint32_t));
        data.emplace_back(type);
    }
}

void
writeEngineTileData(std::ofstream& file, const typeEditorTiles& data) {
    try {
        file.write(reinterpret_cast<const char*>(&data.Size), sizeof(data.Size));
        for (const auto& tile : data.Tiles) {
            auto type = static_cast<uint32_t>(tile.Type.to_ulong());
            file.write(reinterpret_cast<const char*>(&type), sizeof(type));
        }
    } catch (...) {
        std::cerr << "Error writing tiles" << std::endl;
    }
}

}