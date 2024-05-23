#include <common/initializer/sdl.hpp>
#include <iostream>
#include <SDL_image.h>

namespace Common {
SDLInitializer::SDLInitializer(SDL_Window** window, SDL_Renderer** render, const int& w, const int& h, std::string title)
  : window(window)
  , renderer(render)
  , width(w)
  , height(h)
  , windowTitle(std::move(title)) {}

void
SDLInitializer::startup() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Uint32 windowFlags = 0;
    Uint32 renderFlags = 0;
    windowFlags |= SDL_WINDOW_RESIZABLE;
    renderFlags |= SDL_RENDERER_PRESENTVSYNC;

    *window   = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
    *renderer = SDL_CreateRenderer(*window, -1, renderFlags);
}

void
SDLInitializer::shutdown() {
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
}
}