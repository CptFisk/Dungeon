#include <common/jsonAnimation.hpp>
#include <common/jsonHeader.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/graphics.hpp>
#include <graphics/types/baseTexture.hpp>
#include <graphics/types/generatedTexture.hpp>
#include <graphics/types/simpleTexture.hpp>
#include <graphics/types/textureTypes.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <utility/file.hpp>
#include <utility/scale.hpp>

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
            loadSimpleTexture(jsonString);
            break;
        case TextureTypes::AnimatedTexture:
            loadAnimatedTexture(jsonString, TextureTypes::AnimatedTexture);
            break;
        case TextureTypes::GeneratedTexture:
            loadGeneratedTexture(jsonString);
            break;
        case TextureTypes::LightningTexture:
            loadAnimatedTexture(jsonString, TextureTypes::LightningTexture);
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
        auto base = typeSimpleTexture(Common::loadImage(pRenderer, data.File), data.Width, data.Height);
        // Generating viewports
        for (int i = 0; i < data.Length; i++) {
            const auto offset = (data.Column - 1) * data.Width;
            base.addView(SDL_Rect{ (data.Width * i + offset), (data.Height * (data.Row - 1)), data.Width, (data.Height) });
        }
        addTexture<typeSimpleTexture>(data.Name, base, TextureTypes::BaseTexture);
    }
}

void
Graphics::loadAnimatedTexture(const std::string& jsonString, const TextureTypes& type) {
    Common::typeAnimatedTextureData jsonData;
    try {
        jsonData = json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<Common::typeAnimatedTextureData>();
    } catch (const std::exception& e) {
        std::cerr << e.what();
        throw std::runtime_error(e.what());
    }
    for (const auto& data : jsonData.Objects) {
        if (mGraphics.find(data.Name) == mGraphics.end()) {
            auto animation =
              new AnimatedTexture(Common::loadImage(pRenderer, jsonData.File), data.Width, data.Height, data.Ticks, data.Paused);
            // Add alpha channel if lightning

            if (type == TextureTypes::LightningTexture) {

                if(SDL_SetTextureBlendMode(animation->getTexture(), SDL_BLENDMODE_BLEND) != 0)
                    std::cerr << SDL_GetError();
                if(SDL_SetTextureAlphaMod(animation->getTexture(), Utility::Scale(40, 0, 100, 0, 255)) != 0)
                    std::cerr << SDL_GetError();

            }

            for (int i = 0; i < data.Length; i++) {
                const auto offset = (data.Column - 1) * data.Width;
                animation->addViewport(SDL_Rect{ (data.Width * i + offset), (data.Height * (data.Row - 1)), (data.Width), (data.Height) });
            }
            addTexture<AnimatedTexture*>(data.Name, animation, type);
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
            case typeShape::Circle:
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
            case typeShape::Square:
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