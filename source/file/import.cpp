#include <file/import.hpp>
#include <error.hpp>
#include <SDL_image.h>

namespace File{

SDL_Texture*
surfaceToTexture(SDL_Surface* surface, SDL_Renderer*& renderer){
    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    ASSERT_WITH_MESSAGE(texture == nullptr, SDL_GetError())
    return texture;
}


SDL_Surface* readPngFromBuffer(const char* data, const size_t dataSize, SDL_Renderer*& renderer){
    SDL_Surface* surface = nullptr;
    auto rw = SDL_RWFromConstMem(data, dataSize);
    ASSERT_WITH_MESSAGE(rw == nullptr, SDL_GetError())
    surface = IMG_Load_RW(rw, 0);
    ASSERT_WITH_MESSAGE(surface == nullptr, SDL_GetError())
    return surface;
}

}