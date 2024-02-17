#include <common/sdl.hpp>
#include <SDL3_image/SDL_image.h>
#include <iostream>

namespace Common{
SDLInitializer::SDLInitializer(SDL_Window** window, SDL_Renderer** render) :pWindow(window), pRenderer(render){}

void
SDLInitializer::startup() {
    SDL_Init(SDL_INIT_VIDEO);
    const int IMG_INIT_EVERYTHING = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(IMG_INIT_EVERYTHING) & IMG_INIT_EVERYTHING)) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        SDL_Quit();
    }
    Uint32 windowFlags = 0;
    Uint32 renderFlags = 0;
    windowFlags |= SDL_WINDOW_RESIZABLE;
    renderFlags |= SDL_RENDERER_ACCELERATED;
    renderFlags |= SDL_RENDERER_PRESENTVSYNC;

    *pWindow   = SDL_CreateWindow("", 800, 600, windowFlags);
    *pRenderer = SDL_CreateRenderer(*pWindow, nullptr, renderFlags);
}

void
SDLInitializer::shutdown() {
    SDL_DestroyRenderer(*pRenderer);
    SDL_DestroyWindow(*pWindow);
}
}