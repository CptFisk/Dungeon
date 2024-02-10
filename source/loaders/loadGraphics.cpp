#include <engine/structures.hpp>
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
    Engine::HeaderJSON header;
    // Process all the meta-data
    std::vector<BaseTexture> textures;
    for (const auto& file : files) {
        bool              correctType;
        const std::string jsonString = Utility::getFileContent(file.string());
        try {
            header = json::parse(jsonString)[nlohmann::json::json_pointer("/Header")].get<Engine::HeaderJSON>();
        } catch (const std::exception& e) {
            std::cerr << "No header found: " << e.what() << std::endl;
        }
        switch (header.Type) {
            case Engine::BASE_TEXTURE:
                loadBaseTiles(header, jsonString);
                break;
            case Engine::ANIMATED_TEXTURE:
                loadObjectAnimation(header, jsonString);
                break;
            case Engine::GENERATED_TEXTURE:
                loadObjectGeneration(header, jsonString);
                break;
        }
    }
}

void
Graphics::loadBaseTiles(const Engine::HeaderJSON& header, const std::string& jsonString) {
    BaseTextureJSON jsonData;
    try {
        jsonData = json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<BaseTextureJSON>();
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }
    BaseTexture base;
    base.Texture = loadImage(jsonData.File);

    // Generating viewports
    for (int row = 0; row < jsonData.Rows; row++) {
        for (int col = 0; col < jsonData.Columns; col++) {
            base.Views.push_back(SDL_FRect{ static_cast<float>(header.Width) * static_cast<float>(col),
                                            static_cast<float>(header.Height) * static_cast<float>(row),
                                            static_cast<float>(header.Width),
                                            static_cast<float>(header.Height) });
        }
    }
    if (mBaseTextures.find(header.Name) == mBaseTextures.end()) {
        mBaseTextures[header.Name] = base;
    } else {
        throw std::runtime_error("Duplicate texture found");
    }
}

void
Graphics::loadObjectAnimation(const Engine::HeaderJSON& header, const std::string& jsonString) {
    AnimationDataJSON jsonData;
    try {
        jsonData = json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<AnimationDataJSON>();
    } catch (const std::exception& e) {
        std::cerr << e.what();
        throw std::runtime_error(e.what());
    }
    for (const auto& data : jsonData.Animations) {
        if (mAnimatedTextures.find(data.Name) == mAnimatedTextures.end()) {
            AnimatedTexture* animation = new AnimatedTexture(loadImage(jsonData.File), data.Ticks);
            for (int i = 0; i < data.Length; i++) {
                animation->addViewport(
                  SDL_FRect{ static_cast<float>(header.Width) * static_cast<float>(data.Column + i),
                             static_cast<float>(header.Height) * static_cast<float>(data.Row),
                             static_cast<float>(header.Width),
                             static_cast<float>(header.Height) });
            };
            mAnimatedTextures[data.Name] = animation;
        }
    }
}

void
Graphics::loadObjectGeneration(const Engine::HeaderJSON& header, const std::string& jsonString) {
    std::vector<GeneratedObjectJSON> jsonData;
    try {
        jsonData =
          json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<std::vector<GeneratedObjectJSON>>();
    } catch (const std::exception& e) {
        std::cerr << e.what();
        throw std::runtime_error(e.what());
    }
    for (const auto& data : jsonData) {
        switch (data.Shape) {
            case CIRCLE:
                generateCircle(data.Name,
                               header.Height,
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
                               header.Width,
                               header.Height,
                               data.Red1,
                               data.Green1,
                               data.Blue1,
                               Utility::Scale<Uint8>(data.Alpha, 0, 100, 0, 255));
                break;
        }
    }
}

}