#include <file/export.hpp>
#include <error.hpp>
#include <memory>
#include <SDL_image.h>

namespace File{

SDL_Surface*
textureToSurface(SDL_Texture* texture, SDL_Renderer* renderer) {
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

size_t writeToBuffer(SDL_RWops* context, const void* ptr, size_t size, size_t num){
    auto mem = (std::vector<char>*)context->hidden.unknown.data1;
    mem->insert(mem->end(), (char*)ptr, (char*)ptr + size * num);
    return num;
}

bool savePngToBuffer(SDL_Surface* surface, std::vector<char>& buffer){
    auto rw = SDL_AllocRW();
    rw->hidden.unknown.data1 = &buffer;
    rw->write = writeToBuffer;
    return IMG_SavePNG_RW(surface, rw, 0) == 0 ? true : false;
}

}