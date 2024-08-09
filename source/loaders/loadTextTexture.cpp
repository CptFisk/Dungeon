#include <common/jsonTextTexture.hpp>
#include <error.hpp>
#include <graphics/graphics.hpp>
#include <graphics/types/letterTexture.hpp>
#include <nlohmann/json.hpp>

namespace Graphics {

void
Graphics::loadTextTexture(const std::string& jsonString) {
    typeTextTextureData jsonData;
    try {
        jsonData = nlohmann::json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<typeTextTextureData>();
    } catch (const std::exception& e) {
        ASSERT_WITH_MESSAGE(true, e.what());
    }

    for (const auto& data : jsonData.Objects) {
        SDL_Texture* image = Common::loadImage(pRenderer, data.File);
        ASSERT_WITH_MESSAGE(image == nullptr, SDL_GetError())
        int width;
        int height;
        ASSERT_WITH_MESSAGE(SDL_QueryTexture(image, nullptr, nullptr, &width, &height) != 0, SDL_GetError())
        auto texture = new LetterTexture(image, width, height, pRenderer, data.Width, data.Height, data.Length);
        addTexture(data.Name, texture);
    }
}
}