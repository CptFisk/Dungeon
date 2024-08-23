#include <error.hpp>
#include <graphics/graphics.hpp>
#include <graphics/json/jsonUserInterface.hpp>
#include <graphics/types/userInterfaceTexture.hpp>
#include <nlohmann/json.hpp>

namespace Graphics {

void
Graphics::loadUserInterfaceTexture(const std::string& jsonString) {
    typeUserInterfaceTextureData jsonData;
    try {
        jsonData = nlohmann::json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<typeUserInterfaceTextureData>();
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }

    for (const auto& data : jsonData.Objects) {
        auto texture = new UserInterfaceTexture(Common::loadImage(pRenderer, data.File),
                                                data.Width,
                                                data.Height,
                                                data.MarginTop,
                                                data.MarginBottom,
                                                data.MarginLeft,
                                                data.MarginRight);
        // Generating viewports
        for (int i = 0; i < data.Length; i++) {
            const auto offset = (data.Column - 1) * data.Width;
            texture->addViewport(SDL_Rect{ (data.Width * i + offset), (data.Height * (data.Row - 1)), data.Width, (data.Height) });
        }
        addTexture(data.Name, texture);
    }
}

}