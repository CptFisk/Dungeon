#pragma once
#include <SDL3/SDL.h>
#include <common/initializer/initializer.hpp>

namespace Common {
class SDLInitializer : public Initializer {
  public:
    /**
     * @brief Initialize a new SDL instance
     * @param window Window pointer
     * @param render Renderer pointer
     * @param w Window width
     * @param h Window height
     * @param title Title
     */
    SDLInitializer(SDL_Window** window, SDL_Renderer** render, const int& w, const int& h, std::string title);
    void startup() override;
    void shutdown() override;

  private:
  protected:
    const int         width;  // Requested window width
    const int         height; // Requested window height
    SDL_Window**      window;
    SDL_Renderer**    renderer;
    const std::string windowTitle;
};
}