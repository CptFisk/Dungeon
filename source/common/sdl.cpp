#include <SDL_image.h>
#include <common/sdl.hpp>
#include <error.hpp>

namespace Common {
SDL_FRect
newSDL_FRect(const std::pair<int, int>& coords) {
    return newSDL_FRect(coords.first, coords.second);
}

SDL_FRect
newSDL_FRect(const int& x, const int& y) {
    return newSDL_FRect(static_cast<float>(x), static_cast<float>(y));
}

SDL_FRect
newSDL_FRect(const float& x, const float& y) {
    return SDL_FRect{ x * 16.0f, y * 16.0f, 16.0f, 16.0f };
}

SDL_FRect
newSDL_FRectScaled(const int& x, const int& y, const typeScale& scale) {
    return newSDL_FRectScaled(static_cast<float>(x), static_cast<float>(y), scale);
}

SDL_FRect
newSDL_FRectScaled(const float& x, const float& y, const typeScale& scale) {
    return SDL_FRect{ x * 16.0f * static_cast<float>(scale.factorX),
                      y * 16.0f * static_cast<float>(scale.factorY),
                      16.0f * scale.factorX,
                      16.0f * scale.factorY };
}

SDL_Texture*
loadImage(SDL_Renderer* renderer, const std::string& filename) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename.c_str());
    ASSERT_WITH_MESSAGE(texture == nullptr, SDL_GetError())
    SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);
    return texture;
}

TTF_Font*
loadFont(const std::string& path, const int& size) {
    const auto font = TTF_OpenFont(path.c_str(), size);
    ASSERT_WITH_MESSAGE(font == nullptr, SDL_GetError())
    return font;
}

SDL_Surface*
SDL_TextureToSurface(SDL_Texture* texture, SDL_Renderer* renderer) {
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    // Create surface
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    ASSERT_WITH_MESSAGE(surface == nullptr, SDL_GetError)
    ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(renderer, texture) != 0, SDL_GetError)
    ASSERT_WITH_MESSAGE(SDL_RenderReadPixels(renderer, nullptr, surface->format->format, surface->pixels, surface->pitch) != 0,
                        SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(renderer, nullptr) != 0, SDL_GetError())
    return surface;
}
}