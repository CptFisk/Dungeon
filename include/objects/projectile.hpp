#pragma once
#include <SDL3/SDL.h>
#include <graphics/animatedTexture.hpp>

namespace Objects {
class Projectile {
  public:
    Projectile(Graphics::AnimatedTexture* texture, SDL_Renderer* renderer, SDL_Texture* lightning = nullptr);
    void draw();

  private:
  protected:
    SDL_Renderer*              pRenderer;
    Graphics::AnimatedTexture* pProjectile;
    SDL_Texture*               pLightning;
    SDL_FRect                  mCurrentPosition;
    float                      mAngle;
};
}