#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <common/initializer/initializer.hpp>

namespace Common {
class SDLTTFInitializer : public Initializer {
  public:
    SDLTTFInitializer();
    ~SDLTTFInitializer();

    void startup() override;
    void shutdown() override;

  private:
  protected:
};
}