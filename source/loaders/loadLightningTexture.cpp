#include <error.hpp>
#include <graphics/graphics.hpp>
#include <graphics/json/jsonAnimation.hpp>
#include <nlohmann/json.hpp>
#include <utility/scale.hpp>


namespace Graphics {

void
Graphics::loadLightningTexture(const std::string& jsonString) {
    Common::typeAnimatedTextureData jsonData;
    try {
        jsonData = nlohmann::json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<Common::typeAnimatedTextureData>();
    } catch (const std::exception& e) {
        std::cerr << e.what();
        throw std::runtime_error(e.what());
    }
    for (const auto& data : jsonData.Objects) {
        if (mGraphics.find(data.Name) == mGraphics.end()) {
            auto texture =
              new AnimatedTexture(Common::loadImage(pRenderer, jsonData.File), data.Width, data.Height, data.Ticks, data.Paused);
            // Add alpha channel if lightning
            ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(texture->getTexture(), SDL_BLENDMODE_BLEND) != 0, SDL_GetError());
            ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(texture->getTexture(), Utility::Scale(40, 0, 100, 0, 255) != 0), SDL_GetError());
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