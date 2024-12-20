#include <SDL_ttf.h>
#include <graphics/graphics.hpp>
#include <graphics/json/jsonFontTTFTexture.hpp>
#include <graphics/json/jsonFontTexture.hpp>
#include <nlohmann/json.hpp>

namespace Graphics {

void
Graphics::loadFontTexture(const std::string& jsonString) {
    Common::typeFontTextureData jsonData;
    try {
        jsonData = nlohmann::json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<Common::typeFontTextureData>();
    } catch (const std::exception& e) {
        ASSERT_WITH_MESSAGE(false, e.what())
    }
    for (const auto& data : jsonData.Objects) {
        auto font = new FontTexture(Common::loadImage(pRenderer, data.File), pRenderer);
        addTexture(data.Name, font);
    }
}

void
Graphics::loadFontTTFTexture(const std::string& jsonString) {
    Common::typeFontTTFTextureData jsonData;
    try {
        jsonData = nlohmann::json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<Common::typeFontTTFTextureData>();
    } catch (const std::exception& e) {
        ASSERT_WITH_MESSAGE(false, e.what());
    }
    for (const auto& data : jsonData.Objects) {
        auto font = new FontTTF(pRenderer, Common::loadFont(data.File, 6), data.Name);
        addTTFFont(data.Name, font);
    }
}

}