#pragma once
#include <SDL.h>
#include <common/initializer/initializer.hpp>
#include <string>

namespace Common {
class SDLInitializer : public Initializer {
  public:
    /**
     * @brief Initialize a new SDL instance
     * @param window Window pointer
     * @param render Renderer pointer
     * @param w Window width
     * @param h Window height
     * @param fullscreen True for fullscreen
     * @param title Title
     */
    SDLInitializer(SDL_Window*& window, SDL_Renderer*& render, const int& w, const int& h, const bool& fullscreen, std::string title);
    void startup() override;
    void shutdown() override;

  private:
  protected:
    const int         width;      // Requested window width
    const int         height;     // Requested window height
    const bool        fullscreen; // Requested mode
    SDL_Window*&      window;
    SDL_Renderer*&    renderer;
    const std::string windowTitle;
};
}