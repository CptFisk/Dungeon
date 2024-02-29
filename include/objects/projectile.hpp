#pragma once
#include <SDL3/SDL.h>
#include <common/structures.hpp>
#include <graphics/animatedTexture.hpp>
#include <memory>
#include <objects/particle.hpp>
#include <utility>

namespace Objects {
struct typeProjectileStruct {
    Graphics::AnimatedTexture* Projectile; // Projectile texture
    SDL_Texture*               Lightning;  // Lightning texture
    float                      Angle;      // Travel angle
    int                        Duration;   // How far until object is destroyed
    float                      Velocity;   // Velocity of object
};

class Projectile {
    const int PARTICLE_CHANCE = 3; // Chance that a particle spawn

  public:
    Projectile(const typeProjectileStruct&       setup,
               const std::pair<float, float> playerPosition,
               const Common::typeScale       scale,
               SDL_Renderer*                 renderer,
               std::shared_ptr<Particle>     particle); // Constructor
    ~Projectile();

    void draw();           // Draw the object
    int  getNewDuration(); // Calculate and return the new duration
  private:
    void move(); // All functions related to movement
  protected:
    SDL_Renderer*              pRenderer;          // Reference to renderer
    Graphics::AnimatedTexture* pProjectile;        // Reference to animated texture
    SDL_Texture*               pLightning;         // Reference to the lightning, if it exists
    SDL_FRect                  mCurrentPosition;   // Current position of the projectile
    SDL_FRect                  mLightningPosition; // Current position of light (if used)
    float                      mAngle;             // Rotation angle
    const float                mVelocity;          // Velocity
    int                        mDuration;          // Number of ticks, destroyed on 0
    std::shared_ptr<Particle>  mParticle;          // Reference to the particle engine
    bool                       mParticleEnabled;   // If particle was enabled
};
}