#pragma once
#include <SDL3/SDL.h>
#include <graphics/structures.hpp>

namespace Objects {
class Projectile {
  public:
    Projectile(const Graphics::BaseTexture& base, SDL_Renderer* renderer);
    void draw();
  private:
  protected:
    SDL_Texture*  mTexture;
    SDL_Renderer* mRenderer;
    SDL_FRect     mCurrentViewport;
    SDL_FRect     mCurrentPosition;
};
}