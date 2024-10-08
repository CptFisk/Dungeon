#include <error.hpp>
#include <graphics/graphics.hpp>
#include <graphics/json/jsonAnimation.hpp>
#include <nlohmann/json.hpp>


namespace Graphics {

void
Graphics::loadAnimatedTexture(const std::string& jsonString) {
    Common::typeAnimatedTextureData jsonData;
    try {
        jsonData = nlohmann::json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<Common::typeAnimatedTextureData>();
    } catch (const std::exception& e) {
        ASSERT_WITH_MESSAGE(false, e.what());
    }
    for (const auto& data : jsonData.Objects) {
        if (mGraphics.find(data.Name) == mGraphics.end()) {
            auto texture =
              new AnimatedTexture(Common::loadImage(pRenderer, jsonData.File), data.Width, data.Height, data.Ticks, data.Paused);
            for (int i = 0; i < data.Length; i++) {
                const auto offset = (data.Column - 1) * data.Width;
                texture->addViewport(SDL_Rect{ (data.Width * i + offset), (data.Height * (data.Row - 1)), (data.Width), (data.Height) });
            }
            texture->addViewportDone();
            addTexture(data.Name, texture);
        }
    }
}
}