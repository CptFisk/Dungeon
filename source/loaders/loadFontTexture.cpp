#include <graphics/graphics.hpp>
#include <graphics/json/jsonFontTexture.hpp>
#include <nlohmann/json.hpp>
#include <SDL_ttf.h>


namespace Graphics {

void
Graphics::loadFontTexture(const std::string& jsonString) {
    Common::typeFontTextureData jsonData;
    try {
        jsonData = nlohmann::json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<Common::typeFontTextureData>();
    } catch (const std::exception& e) {
        ASSERT_WITH_MESSAGE(false, e.what());
    }
    for (const auto& data : jsonData.Objects) {
        auto font = new Font(Common::loadFont(data.File, 24),data.Name);
        addFont(data.Name, font);
    }
}

}