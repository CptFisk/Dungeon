#include <cmath>
#include <graphics/graphics.hpp>
#include <iostream>

namespace Graphics {
Graphics::Graphics(SDL_Renderer* renderer, float& scaleX, float& scaleY)
  : pRenderer(renderer)
  , mScaleX(scaleX)
  , mScaleY(scaleY) {
    loadGraphics("rsrc");
}

void
Graphics::updateAnimatedTexture() {
    for(auto &[name, texture] : mAnimatedTextures){
        texture->nextViewport();
    }
}

Graphics::~Graphics() {
    for (auto [name, texture] : mTextures) {
        SDL_DestroyTexture(texture);
    }

    for (auto [name, obj] : mAnimatedTextures) {
        delete obj;
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
    auto surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
    SDL_FillSurfaceRect(surface, nullptr, SDL_MapRGB(surface->format, r, g, b));
    auto square = SDL_CreateTextureFromSurface(pRenderer, surface);
    SDL_SetTextureBlendMode(square, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(square, a);
    SDL_DestroySurface(surface);
    mTextures[name] = square;
}

void
Graphics::generateCircle(const std::string& name,
                         const float&       radius,
                         const Uint8&       r,
                         const Uint8&       g,
                         const Uint8&       b,
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

    int startR = 251;
    int startG = 255;
    int startB = 226;

    int endR = 226;
    int endG = 230;
    int endB = 203;

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
    mTextures[name] = circleTexture;
}

SDL_Texture*
Graphics::getTexture(const std::string& name) {
    return mTextures[name];
}

BaseTexture
Graphics::getBaseTexture(const std::string& name) {
    return mBaseTextures[name];
}

AnimatedTexture*
Graphics::getAnimatedTexture(const std::string& name) {
    return mAnimatedTextures[name];
}

}