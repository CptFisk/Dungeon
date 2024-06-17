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
            typeWarpCoordinate origin{};
            typeWarpCoordinate destination{};

            uint8_t fileLength;

            file.read(reinterpret_cast<char*>(&origin), sizeof(origin));
            file.read(reinterpret_cast<char*>(&destination), sizeof(destination));

            //Get the length of the filename
            file.read(reinterpret_cast<char*>(&fileLength), sizeof(fileLength));
            char* filename = new char[fileLength + 1]{};
            file.read(filename, fileLength);

            data.emplace_back(origin, destination, filename);
            // Cleanup
            delete[] filename;
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

            // Handles filename
            const auto filenameLength = static_cast<uint8_t>(warp.Filename.size());
            file.write(reinterpret_cast<const char*>(filenameLength), sizeof(filenameLength)); // Write length
            file.write(warp.Filename.c_str(), filenameLength);
        } catch (...) {
            std::cerr << "Error writing warp data" << std::endl;
        }
    }
}
}