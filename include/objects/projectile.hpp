#pragma once
#include <SDL3/SDL.h>
#include <graphics/animatedTexture.hpp>

namespace Objects {
struct ProjectileStruct {
    Graphics::AnimatedTexture* Projectile;
    SDL_Texture*               Lightning;
    float                      Angle;
    int                        Duration;
    float                      Velocity;
};

class Projectile {
  public:
    Projectile(const ProjectileStruct& setup, SDL_Renderer* renderer);
    void draw();

  private:
    void calculatePosition();

  protected:
    SDL_Renderer*              pRenderer;          // Reference to renderer
    Graphics::AnimatedTexture* pProjectile;        // Reference to animated texture
    SDL_Texture*               pLightning;         // Reference to the lightning, if it exists
    SDL_FRect                  mCurrentPosition;   // Current position of the projectile
    SDL_FRect                  mLightningPosition; // Current position of light (if used)
    float                      mAngle;             // Rotation angle
    const float                mVelocity;          // Velocity
    int                        mDuration;          // Number of ticks, destroyed on 0
};
}