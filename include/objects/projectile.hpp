#pragma once
#include <SDL3/SDL.h>

namespace Objects{
class Projectile{
  public:
    Projectile(SDL_Texture* texture, SDL_Renderer* renderer);
  private:
  protected:
    SDL_Texture* mTexture;
    SDL_Renderer* mRenderer;
};
}