#pragma once
#include <SDL.h>

namespace Engine::Debug{
static int getFPS(){
    static int frameCount = 0;
    static Uint32 startTime = SDL_GetTicks();
    static int fps = 0;

    frameCount++;
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - startTime;

    if(elapsedTime > 1000){
        fps = frameCount / (elapsedTime / 1000.f);
        frameCount = 0;
        startTime = currentTime;
    }
    return fps;
}
}