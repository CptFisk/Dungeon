#include <global.hpp>
#include <iostream>
#include <level/types/warp.hpp>

namespace Level::File {

void
readWarpData(std::ifstream& file, std::vector<typeWarpData>& data) {
    uint16_t readSize;

    file.read(reinterpret_cast<char*>(&readSize), sizeof(readSize));
    for (int i = 0; i < readSize; i++) {
        try {
            typeMapCoordinate origin{};
            typeMapCoordinate destination{};

            file.read(reinterpret_cast<char*>(&origin), sizeof(origin));
            file.read(reinterpret_cast<char*>(&destination), sizeof(destination));

            data.emplace_back(origin, destination);

        } catch (...) {
            std::cerr << "Error reading doors" << std::endl;
        }
    }
}

void
writeWarpData(std::ofstream& file, const std::vector<typeWarpData>& data) {
    const auto numWarps = UINT16(data.size());
    file.write(reinterpret_cast<const char*>(&numWarps), sizeof(numWarps));

    for (const auto& warp : data) {
        try {
            file.write(reinterpret_cast<const char*>(&warp.Origin), sizeof(warp.Origin));
            file.write(reinterpret_cast<const char*>(&warp.Destination), sizeof(warp.Destination));

        } catch (...) {
            std::cerr << "Error writing warp data" << std::endl;
        }
    }
}
}