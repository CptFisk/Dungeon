#include <global.hpp>
#include <iostream>
#include <file/types/editorHeader.hpp>

namespace File {
void
readHeaderData(std::ifstream& file, typeHeaderData& data) {
    try {
        // Read header data
        file.read(reinterpret_cast<char*>(&data.MapCoordinate), sizeof(typeHeaderData::MapCoordinate));
        file.read(reinterpret_cast<char*>(&data.Colour), sizeof(typeHeaderData::Colour));

        // Get size of first vector
        uint8_t readSize;
        file.read(reinterpret_cast<char*>(&readSize), sizeof(uint8_t));
        for (int i = 0; i < readSize; i++) {
            uint8_t dataSize;
            file.read(reinterpret_cast<char*>(&dataSize), sizeof(uint8_t));
            char* content = new char[dataSize + 1]{};
            file.read(content, dataSize);
            data.OnLoad.emplace_back(content);
            delete[] content;
        }
        // Get size of second vector

        file.read(reinterpret_cast<char*>(&readSize), sizeof(uint8_t));
        for (int i = 0; i < readSize; i++) {
            uint8_t dataSize;
            file.read(reinterpret_cast<char*>(&dataSize), sizeof(uint8_t));
            char* content = new char[dataSize + 1]{};
            file.read(content, dataSize);
            data.OnExit.emplace_back(content);
            delete[] content;
        }
    } catch (...) {
        std::cerr << "Cant read header data" << std::endl;
    }
}

void
writeHeaderData(std::ofstream& file, const typeHeaderData& data) {
    try {
        file.write(reinterpret_cast<const char*>(&data.MapCoordinate), sizeof(data.MapCoordinate));
        file.write(reinterpret_cast<const char*>(&data.Colour), sizeof(data.Colour));

        const auto onLoadSize = UINT8(data.OnLoad.size());
        const auto onExitSize = UINT8(data.OnExit.size());

        file.write(reinterpret_cast<const char*>(&onLoadSize), sizeof(onLoadSize));
        for (const auto& content : data.OnLoad) {
            const auto contentSize = UINT8(content.size());
            file.write(reinterpret_cast<const char*>(&contentSize), sizeof(contentSize));
            file.write(content.c_str(), contentSize);
        }

        file.write(reinterpret_cast<const char*>(&onExitSize), sizeof(onExitSize));
        for (const auto& content : data.OnExit) {
            const auto contentSize = UINT8(content.size());
            file.write(reinterpret_cast<const char*>(&contentSize), sizeof(contentSize));
            file.write(content.c_str(), contentSize);
        }
    } catch (...) {
        std::cerr << "Cant write header data" << std::endl;
    }
}
}
