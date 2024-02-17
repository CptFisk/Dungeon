#pragma once
#include <SDL3/SDL.h>
#include <common/initializer.hpp>
#include <memory>

namespace Editor {
class Editor {
  public:
    Editor();
    ~Editor();

    void startup(); // Load all functions related to startup
  protected:
  private:
    std::unique_ptr<Common::InitHandler> mInitHandler;

    SDL_Window*   pWindow;
    SDL_Renderer* pRenderer;
};
}