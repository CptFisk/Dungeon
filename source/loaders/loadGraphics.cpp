#include <common/structures.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/graphics.hpp>
#include <graphics/structures.hpp>
#include <graphics/types/simpleTexture.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <utility/file.hpp>
#include <utility/scale.hpp>

using json = nlohmann::json;

namespace Graphics {
void
Graphics::loadGraphics(const std::string& folderPath) {
    //Fetch all the folders
    const auto folders = Utility::getFolders(folderPath);
    for(const auto& folder: folders){
        //Now we fetch all the files inside that folder that match the criteria
        const auto files = Utility::getFiles(folder.string(), ".json");

    }
    auto                   files  = Utility::getFiles(folderPath, ".json");
    Common::typeHeaderJSON header = {};
    // Process all the meta-data
    std::vector<typeSimpleTexture> textures;
    for (const auto& file : files) {
        const std::string jsonString = Utility::getFileContent(file.string());
        try {
            header = json::parse(jsonString)[nlohmann::json::json_pointer("/Header")].get<Common::typeHeaderJSON>();
        } catch (const std::exception& e) {
            std::cerr << "No header found: " << e.what() << std::endl;
        }
        switch (header.Type) {
            case Common::BASE_TEXTURE:
                loadSimpleTexture(jsonString);
                break;
            case Common::ANIMATED_TEXTURE:
                loadAnimatedTexture(jsonString);
                break;
            case Common::GENERATED_TEXTURE:
                loadGeneratedTexture(jsonString);
                break;
        }
    }
}

void
Graphics::loadSimpleTexture(const std::string& jsonString) {
    typeBaseTextureData jsonData;
    try {
        jsonData = json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<typeBaseTextureData>();
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }

    for (const auto& data : jsonData.Objects) {
        auto base = typeSimpleTexture(loadImage(data.File), data.Width, data.Height);
        // Generating viewports
        for (int i = 0; i < data.Length; i++) {
            const auto offset = (data.Column - 1) * data.Width;
            base.addView(SDL_FRect{ static_cast<float>(data.Width * i + offset),
                                            static_cast<float>(data.Height * (data.Row - 1)),
                                            static_cast<float>(data.Width),
                                            static_cast<float>(data.Height) });
        }
        addTexture<typeSimpleTexture>(data.Name, base, SIMPLE_TEXTURE);
    }
}

void
Graphics::loadAnimatedTexture(const std::string& jsonString) {
    typeAnimatedTextureData jsonData;
    try {
        jsonData = json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<typeAnimatedTextureData>();
    } catch (const std::exception& e) {
        std::cerr << e.what();
        throw std::runtime_error(e.what());
    }
    for (const auto& data : jsonData.Objects) {
        if (mGraphics.find(data.Name) == mGraphics.end()) {
            auto animation = new AnimatedTexture(loadImage(jsonData.File), data.Ticks);
            for (int i = 0; i < data.Length; i++) {
                const auto offset = (data.Column - 1) * data.Width;
                animation->addViewport(SDL_FRect{ static_cast<float>(data.Width * i + offset),
                                                  static_cast<float>(data.Height * (data.Row - 1)),
                                                  static_cast<float>(data.Width),
                                                  static_cast<float>(data.Height) });
            }
            addTexture<AnimatedTexture*>(data.Name, animation, ANIMATED_TEXTURE);
        }
    }
}

void
Graphics::loadGeneratedTexture(const std::string& jsonString) {
    typeGeneratedTextureData jsonData;
    try {
        jsonData = json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<typeGeneratedTextureData>();
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }
    for (const auto& data : jsonData.Objects) {
        switch (data.Shape) {
            case CIRCLE:
                generateCircle(data.Name,
                               static_cast<float>(data.Height),
                               data.Red1,
                               data.Red2,
                               data.Green1,
                               data.Green2,
                               data.Blue1,
                               data.Blue2,
                               Utility::Scale<Uint8>(data.Alpha, 0, 100, 0, 255));
                break;
            case SQUARE:
                generateSquare(data.Name,
                               data.Width,
                               data.Height,
                               data.Red1,
                               data.Green1,
                               data.Blue1,
                               Utility::Scale<Uint8>(data.Alpha, 0, 100, 0, 255));
                break;
        }
    }
}

}