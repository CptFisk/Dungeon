#include <SDL3_image/SDL_image.h>
#include <common/initializer/sdl.hpp>
#include <iostream>

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

    *window   = SDL_CreateWindow(windowTitle.c_str(), width, height, windowFlags);
    *renderer = SDL_CreateRenderer(*window, nullptr, renderFlags);
}

void
SDLInitializer::shutdown() {
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
}
}