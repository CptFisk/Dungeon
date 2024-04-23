#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

namespace Utility {
    /**
     * @brief Read the data from a file
     * @param filePath Path to the file
     * @return Contents as a string
     */
    std::string getFileContent(const std::string &filePath);

    /**
     * @brief Returns a list of all the folders inside a folder
     * @param rootFolder
     * @return Vector with all folders
     */
    std::vector<std::filesystem::path>
    getFolders(const std::string& rootFolder);

    /**
     * @brief Return all the files with the correct extension from a folder
     * @param folderPath Path to folder
     * @param extension Extension (.json, .txt)
     * @return Vector with all files matching the criteria
     */
    std::vector<std::filesystem::path>
    getFiles(const std::string& folderPath, const std::string& extension);
}