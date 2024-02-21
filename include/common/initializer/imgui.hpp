#pragma once
#include <SDL3/SDL.h>
#include <common/initializer/initializer.hpp>
#include <imgui.h>


namespace Common {
class ImGuiInitializer : public Initializer {
  public:
    ImGuiInitializer(SDL_Window** window, SDL_Renderer** render);
    void startup();
    void shutdown();

  private:
  protected:
    SDL_Window**   pWindow;
    SDL_Renderer** pRenderer;
    ImGuiIO&       io;
};
}