#pragma once
#include <string>
#include <filesystem>
#include <fstream>

namespace Utility {
    std::string getFileContent(const std::string &filePath);

    std::vector<std::filesystem::path>
    getFiles(const std::string& folderPath, const std::string& extension);
}