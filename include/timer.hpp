#pragma once
#include <SDL3/SDL.h>

namespace Engine{
class Timer{
  public:
    Timer() : mTicks(0){};
    void start(){mTicks = SDL_GetTicks();};
    Uint32 getTicks(){
        return SDL_GetTicks() - mTicks;
    }
  protected:
      private:
    Uint32 mTicks;
};
}