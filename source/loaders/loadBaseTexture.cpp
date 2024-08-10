#include <graphics/graphics.hpp>
#include <graphics/json/jsonBaseTexture.hpp>
#include <nlohmann/json.hpp>


namespace Graphics {

void
Graphics::loadBaseTexture(const std::string& jsonString) {
    typeBaseTextureData jsonData;
    try {
        jsonData = nlohmann::json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<typeBaseTextureData>();
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }

    for (const auto& data : jsonData.Objects) {
        auto texture = new BaseTexture(Common::loadImage(pRenderer, data.File), data.Width, data.Height);
        // Generating viewports
        for (int i = 0; i < data.Length; i++) {
            const auto offset = (data.Column - 1) * data.Width;
            texture->addViewport(SDL_Rect{ (data.Width * i + offset), (data.Height * (data.Row - 1)), data.Width, (data.Height) });
        }
        addTexture(data.Name, texture);
    }
}

}