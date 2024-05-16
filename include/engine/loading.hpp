#pragma once
#include <iostream>
#include <graphics/graphics.hpp>

namespace Engine{

class LoadingScreen{
  public:
    LoadingScreen(SDL_Renderer** renderer);

  protected:
  private:
    SDL_Renderer* pRender;
};
}