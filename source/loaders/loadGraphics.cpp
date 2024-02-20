#include <common/structures.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/graphics.hpp>
#include <graphics/structures.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <utility/file.hpp>
#include <utility/scale.hpp>

using json = nlohmann::json;

namespace Graphics {
void
Graphics::loadGraphics(const std::string& folderPath) {
    auto               files = Utility::getFiles(folderPath, ".json");
    Common::typeHeaderJSON header;
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
                loadBaseTiles(header, jsonString);
                break;
            case Common::ANIMATED_TEXTURE:
                loadObjectAnimation(header, jsonString);
                break;
            case Common::GENERATED_TEXTURE:
                loadObjectGeneration(header, jsonString);
                break;
        }
    }
}

void
Graphics::loadBaseTiles(const Common::typeHeaderJSON& header, const std::string& jsonString) {
    typeBaseTextureData jsonData;
    try {
        jsonData = json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<typeBaseTextureData>();
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }

    for (const auto& data : jsonData.Objects) {
        typeSimpleTexture base;
        base.Texture = loadImage(data.File);
        // Generating viewports
        for (int i = 0; i < data.Length; i++) {
            base.Views.push_back(SDL_FRect{ static_cast<float>(data.Width * data.Column * i),
                                            static_cast<float>(data.Height * (data.Row - 1)),
                                            static_cast<float>(data.Width),
                                            static_cast<float>(data.Height) });
        }
        mBaseTextures[data.Name] = base;
    }
}

void
Graphics::loadObjectAnimation(const Common::typeHeaderJSON& header, const std::string& jsonString) {
    typeAnimatedTextureData jsonData;
    try {
        jsonData = json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<typeAnimatedTextureData>();
    } catch (const std::exception& e) {
        std::cerr << e.what();
        throw std::runtime_error(e.what());
    }
    for (const auto& data : jsonData.Objects) {
        if (mAnimatedTextures.find(data.Name) == mAnimatedTextures.end()) {
            auto animation = new AnimatedTexture(loadImage(jsonData.File), data.Ticks);
            for (int i = 0; i < data.Length; i++) {
                animation->addViewport(SDL_FRect{ static_cast<float>(data.Width * data.Column *i),
                                                  static_cast<float>(data.Height * (data.Row - 1)),
                                                  static_cast<float>(data.Width),
                                                  static_cast<float>(data.Height) });
            };
            mAnimatedTextures[data.Name] = animation;
        }
    }
}

void
Graphics::loadObjectGeneration(const Common::typeHeaderJSON& header, const std::string& jsonString) {
    GeneratedDataJSON jsonData;
    try {
        jsonData = json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<GeneratedDataJSON>();
    } catch (const std::exception& e) {
        std::cerr << e.what();
        //throw std::runtime_error(e.what());
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