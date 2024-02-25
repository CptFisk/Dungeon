#include <common/initializer/sdl.hpp>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

namespace Common{
SDLInitializer::SDLInitializer(SDL_Window** window, SDL_Renderer** render, const std::string& title) :pWindow(window), pRenderer(render), mTitle(title){}

void
SDLInitializer::startup() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    Uint32 windowFlags = 0;
    Uint32 renderFlags = 0;
    windowFlags |= SDL_WINDOW_RESIZABLE;
    renderFlags |= SDL_RENDERER_ACCELERATED;
    renderFlags |= SDL_RENDERER_PRESENTVSYNC;

    *pWindow   = SDL_CreateWindow(mTitle.c_str(), 800, 600, windowFlags);
    *pRenderer = SDL_CreateRenderer(*pWindow, nullptr, renderFlags);
}

void
SDLInitializer::shutdown() {
    SDL_DestroyRenderer(*pRenderer);
    SDL_DestroyWindow(*pWindow);
}
}