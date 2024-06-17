#include <level/types/assets.hpp>
#include <iostream>
#include <global.hpp>

namespace Level::File{

void
readAssets(std::ifstream& file, typeAssets& data){
    uint16_t readSize;
    file.read(reinterpret_cast<char*>(&readSize), sizeof(readSize));

    for (uint16_t i = 0; i < readSize; i++) {
        try {
            uint8_t assetLength = {};
            file.read(reinterpret_cast<char*>(&assetLength), sizeof(assetLength));
            char* assetName = new char[assetLength + 1]{};
            file.read(assetName, assetLength);
            data.Assets.emplace_back(assetName);
            delete[] assetName; // Clear memory
        }catch(...){
            std::cerr << "Error reading assets" << std::endl;
        }
    }
}

void writeAssets(std::ofstream& file, const typeAssets& data){
    //Get the number os assets in map and store it as uint16_t
    const auto numAssets = UINT16(data.Assets.size());
    file.write(reinterpret_cast<const char*>(&numAssets), sizeof(uint16_t));

    for (const auto& asset : data.Assets) {
        try {
            const auto assetNameLength = static_cast<uint8_t>(asset.size());
            file.write(reinterpret_cast<const char*>(&assetNameLength), sizeof(assetNameLength)); // Write length
            file.write(asset.c_str(), assetNameLength);
        }catch(...){
            std::cerr << "Error writing assets" << std::endl;
        }
    }
}

}