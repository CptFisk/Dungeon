#include <graphics/graphics.hpp>
#include <iostream>

namespace Graphics {
void
Graphics::generateSquare(const std::string& name,
                         const int&         width,
                         const int&         height,
                         const Uint8&       r,
                         const Uint8&       g,
                         const Uint8&       b,
                         const Uint8&       a) {
    auto surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
    if (surface == nullptr) {
        std::cerr << SDL_GetError() << std::endl;
    }

    if (SDL_FillSurfaceRect(surface, nullptr, SDL_MapRGB(surface->format, r, g, b)) != 0)
        std::cerr << SDL_GetError() << std::endl;
    auto squareTexture = SDL_CreateTextureFromSurface(pRenderer, surface);
    if (squareTexture == nullptr)
        std::cerr << SDL_GetError() << std::endl;
    if (SDL_SetTextureBlendMode(squareTexture, SDL_BLENDMODE_BLEND) != 0)
        std::cerr << SDL_GetError() << std::endl;
    if (SDL_SetTextureAlphaMod(squareTexture, a) != 0)
        std::cerr << SDL_GetError() << std::endl;
    SDL_DestroySurface(surface);

    if (SDL_RenderTexture(pRenderer, squareTexture, nullptr, nullptr) != 0)
        std::cerr << SDL_GetError();
    addTexture<SDL_Texture*>(name, squareTexture, GENERATED_TEXTURE);
    SDL_DestroySurface(surface);
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
    auto surface = SDL_CreateSurface(radius * 2, radius * 2, SDL_PIXELFORMAT_RGBA32);
    // Surface check
    if (!surface) {
        std::cerr << "SDL_CreateRGBSurface failed: " << SDL_GetError() << std::endl;
    }

    int centerX     = radius;
    int centerY     = radius;
    int centerAlpha = 255;
    int edgeAlpha   = 0;

    int startR = r1;
    int startG = g1;
    int startB = b1;

    int endR = r2;
    int endG = g2;
    int endB = b2;

    for (int y = 0; y < radius * 2; ++y) {
        for (int x = 0; x < radius * 2; ++x) {
            float distance = std::hypot(x - centerX, y - centerY);

            // Check if the pixel is within the circle
            if (distance <= radius) {
                // Interpolate alpha linearly between centerAlpha and edgeAlpha
                Uint8 alpha = static_cast<Uint8>(centerAlpha + (edgeAlpha - centerAlpha) * (distance / radius));
                Uint8 red   = static_cast<Uint8>(startR + (endR - startR) * (distance / radius));
                Uint8 green = static_cast<Uint8>(startG + (endG - startG) * (distance / radius));
                Uint8 blue  = static_cast<Uint8>(startB + (endB - startB) * (distance / radius));

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

    SDL_DestroySurface(surface);
    addTexture<SDL_Texture*>(name, circleTexture, GENERATED_TEXTURE);
}
}