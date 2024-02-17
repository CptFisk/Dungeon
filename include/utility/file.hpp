#pragma once
#include <string>
#include <filesystem>
#include <fstream>

namespace Utility {
    std::string getFileContent(const std::string &filePath);

    std::vector<std::filesystem::path>
    getFiles(const std::string& folderPath, const std::string& extension);

    template<typename T>
    void writeStructToFile(const T* data, std::size_t dataSize, const std::string& filename){
        std::ofstream file(filename.c_str(), std::ios::out | std::ios::binary);

        // Write the struct data to the file
        file.write(reinterpret_cast<const char*>(data), dataSize);

        // Close the file
        file.close();
    }
}