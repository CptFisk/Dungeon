#pragma once
#include <graphics/graphics.hpp>
#include <iostream>
#include <mutex>
namespace Engine {

class LoadingScreen {
  public:
    LoadingScreen(SDL_Renderer*& renderer, std::mutex& mutex);
    ~LoadingScreen() = default;
    void run();
  protected:
  private:
    SDL_Renderer* pRender;
    SDL_Texture*  pLogo;
    std::mutex& mMutex;
};
}