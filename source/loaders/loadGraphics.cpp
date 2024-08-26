#include <graphics/graphics.hpp>
#include <graphics/json/jsonHeader.hpp>
#include <nlohmann/json.hpp>
#include <utility/file.hpp>

using json = nlohmann::json;

namespace Graphics {
void
Graphics::loadGraphics(const std::string& folderPath) {
    // Fetch all the folders
    const auto folders = Utility::getFolders(folderPath);
    for (const auto& folder : folders) {
        // Now we fetch all the files inside that folder that match the criteria
        const auto files = Utility::getFiles(folder.string(), ".json");
        // Load all the files
        for (const auto& file : files) {
            loadJSON(file.string());
        }
    }
}

void
Graphics::loadJSON(const std::string& fileName) {
    typeHeaderJSON header = {};
    // Process all the meta-data
    const std::string jsonString = Utility::getFileContent(fileName);
    try {
        header = json::parse(jsonString)[nlohmann::json::json_pointer("/Header")].get<typeHeaderJSON>();
    } catch (const std::exception& e) {
        std::cerr << "No header found: in " << fileName << std::endl << e.what() << std::endl;
    }
    switch (header.Type) {
        case TextureTypes::BaseTexture:
            loadBaseTexture(jsonString);
            break;
        case TextureTypes::AnimatedTexture:
            loadAnimatedTexture(jsonString);
            break;
        case TextureTypes::GeneratedTexture:
            loadGeneratedTexture(jsonString);
            break;
        case TextureTypes::LightningTexture:
            loadLightningTexture(jsonString);
            break;
        case TextureTypes::UserInterface:
            loadUserInterfaceTexture(jsonString);
            break;
        case TextureTypes::Font:
            loadFontTexture(jsonString);
            break;
    }
}

}