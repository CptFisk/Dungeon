#pragma once
#include <SDL3/SDL.h>
#include <graphics/animatedTexture.hpp>

namespace Objects {
class Projectile {
  public:
    Projectile(Graphics::AnimatedTexture* texture, SDL_Renderer* renderer);
    void draw();

  private:
  protected:
    SDL_Renderer*              mRenderer;
    Graphics::AnimatedTexture* mTexture;
    SDL_FRect                  mCurrentPosition;
    float                      mAngle;
};
}