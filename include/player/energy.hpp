#pragma once
#include <SDL3/SDL.h>
#include <common/structures.hpp>
#include <graphics/structures.hpp>

namespace Player {
class Energy {
  public:
    Energy(const Common::typeScale& scale, const Graphics::BaseTexture& baseTexture, SDL_Renderer* renderer); // Constructor
    ~Energy();

    void draw();

  protected:
  private:
    float                       mEnergy;
    SDL_Renderer*               pRenderer;
    const Graphics::BaseTexture mBaseTexture;
};
}