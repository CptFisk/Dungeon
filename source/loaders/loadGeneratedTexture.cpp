#include <common/jsonGeneratedTexture.hpp>
#include <error.hpp>
#include <graphics/graphics.hpp>
#include <nlohmann/json.hpp>
#include <utility/scale.hpp>

namespace Graphics {

void
Graphics::loadGeneratedTexture(const std::string& jsonString) {
    typeGeneratedTextureData jsonData;
    try {
        jsonData = nlohmann::json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<typeGeneratedTextureData>();
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

void
Graphics::generateSquare(const std::string& name,
                         const int&         width,
                         const int&         height,
                         const Uint8&       r,
                         const Uint8&       g,
                         const Uint8&       b,
                         const Uint8&       a) {
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    ASSERT_WITH_MESSAGE(surface == nullptr, "Surface is nullptr");
    ASSERT_WITH_MESSAGE(SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, r, g, b)) != 0, "Cant fill rectangle");
    auto squareTexture = SDL_CreateTextureFromSurface(pRenderer, surface);
    ASSERT_WITH_MESSAGE(squareTexture == nullptr, "squareTexture is nullptr");

    ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(squareTexture, SDL_BLENDMODE_BLEND) != 0, "Cant set blend-mode");
    ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(squareTexture, a) != 0, "Cant apply alpha channel");
    SDL_FreeSurface(surface);

    ASSERT_WITH_MESSAGE(SDL_RenderCopy(pRenderer, squareTexture, nullptr, nullptr) != 0, "Cant render texture");
    addTexture<SDL_Texture*>(name, squareTexture, TextureTypes::GeneratedTexture);
}

void
Graphics::generateCircle(const std::string& name,   // Name of texture
                         const float&       radius, // Radius
                         const Uint8&       r1,     // Start red color
                         const Uint8&       r2,     // End red color
                         const Uint8&       g1,     // Start green color
                         const Uint8&       g2,     // End green color
                         const Uint8&       b1,     // Start blue color
                         const Uint8&       b2,     // End blue color
                         const Uint8&       a) {

    auto surface =
      SDL_CreateRGBSurfaceWithFormat(0, static_cast<int>(radius) * 2, static_cast<int>(radius) * 2, 32, SDL_PIXELFORMAT_RGBA32);
    // Surface check
    ASSERT_WITH_MESSAGE(surface == nullptr, "Surface is nullptr");

    int centerX     = static_cast<int>(radius);
    int centerY     = static_cast<int>(radius);
    int centerAlpha = 255;
    int edgeAlpha   = 0;

    int startR = r1;
    int startG = g1;
    int startB = b1;

    int endR = r2;
    int endG = g2;
    int endB = b2;

    for (int y = 0; y < static_cast<int>(radius * 2); ++y) {
        for (int x = 0; x < static_cast<int>(radius * 2); ++x) {
            auto distance = static_cast<float>(std::hypot(x - centerX, y - centerY));

            // Check if the pixel is within the circle
            if (distance <= radius) {
                // Interpolate alpha linearly between centerAlpha and edgeAlpha
                auto alpha = static_cast<Uint8>(static_cast<float>(centerAlpha + (edgeAlpha - centerAlpha)) * (distance / radius));
                auto red   = static_cast<Uint8>(static_cast<float>(startR + (endR - startR)) * (distance / radius));
                auto green = static_cast<Uint8>(static_cast<float>(startG + (endG - startG)) * (distance / radius));
                auto blue  = static_cast<Uint8>(static_cast<float>(startB + (endB - startB)) * (distance / radius));

                auto pixel      = (Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
                *(Uint32*)pixel = SDL_MapRGBA(surface->format, red, green, blue, alpha);
            }
        }
    }

    auto circleTexture = SDL_CreateTextureFromSurface(pRenderer, surface);
    SDL_SetTextureBlendMode(circleTexture, SDL_BLENDMODE_ADD);
    SDL_SetTextureAlphaMod(circleTexture, a);
    if (!circleTexture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);
    addTexture<SDL_Texture*>(name, circleTexture, TextureTypes::GeneratedTexture);
}
}