#include <fstream>
#include <sstream>
#include <utility/file.hpp>
#include <vector>

namespace Utility {
std::string
getFileContent(const std::string& filePath) {
    const std::string fullPath = filePath;
    std::ifstream     file(fullPath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filePath);
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> content(size);
    if (!file.read(content.data(), size)) {
        throw std::runtime_error("Error reading file: " + filePath);
    }

    return std::string(content.begin(), content.end());
}

std::vector<std::filesystem::path>
getFolders(const std::string& rootFolder) {
    std::filesystem::path              folder(rootFolder);
    std::vector<std::filesystem::path> folders;
    if (std::filesystem::exists(folder) && std::filesystem::is_directory(folder)) {
        for (const auto& entry : std::filesystem::directory_iterator(folder)) {
            if (entry.is_directory())
                folders.push_back(entry);
        }
    }
    return folders;
}

std::vector<std::filesystem::path>
getFiles(const std::string& folderPath, const std::string& extension) {
    std::filesystem::path              folder(folderPath); // Load the folder path
    std::vector<std::filesystem::path> files;
    if (std::filesystem::exists(folder) && std::filesystem::is_directory(folder)) {
        for (const auto& entry : std::filesystem::directory_iterator(folder)) {
            // Checking all files
            if (entry.is_regular_file() && entry.path().extension() == extension) {
                files.push_back(entry);
            }
        }
    } else {
        throw std::runtime_error(folderPath + " is not a valid folder");
    }
    return files;
}
}
