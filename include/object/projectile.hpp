#pragma once
#include <SDL.h>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/drawData.hpp>
#include <memory>
#include <object/particle.hpp>
#include <utility>

namespace Objects {
struct typeProjectileStruct {
    Graphics::AnimatedTexture* Projectile; // Projectile texture
    SDL_Texture*               Lightning;  // Lightning texture
    double                     Angle;      // Travel angle
    int                        Duration;   // How far until object is destroyed
    float                      Velocity;   // Velocity of object
};

class Projectile {
    const int PARTICLE_CHANCE = 3; // Chance that a particle spawn

  public:
    Projectile(const typeProjectileStruct&    setup,
               const std::pair<float, float>& playerPosition,
               SDL_Renderer*                  renderer,
               const std::shared_ptr<Particle>& particle); // Constructor
    ~Projectile();

    SDL_FRect* getPosition(); // Returns a pointer to the current position

    [[nodiscard]] int                          getNewDuration(); // Calculate and return the new duration
    [[nodiscard]] int                          getDamage() const;
    [[nodiscard]] Graphics::typeDrawData       getLightning();  // Return draw data for lightning
    [[nodiscard]] Graphics::typeDrawDataAngled getProjectile(); // Return draw data for the projectile

    void move(); // All functions related to movement
  private:
  protected:
    SDL_Renderer*              pRenderer;          // Reference to renderer
    Graphics::AnimatedTexture* pProjectile;        // Reference to animated texture
    SDL_Texture*               pLightning;         // Reference to the lightning, if it exists
    SDL_FRect                  mCurrentPosition;   // Current position of the projectile
    SDL_FRect                  mLightningPosition; // Current position of light (if used)
    int                        mDamage;
    double                     mAngle;           // Rotation angle
    const float                mVelocity;        // Velocity
    int                        mDuration;        // Number of ticks, destroyed on 0
    std::shared_ptr<Particle>  mParticle;        // Reference to the particle engine
    bool                       mParticleEnabled; // If particle was enabled
};
}