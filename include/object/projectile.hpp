#pragma once
#include <SDL.h>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/baseTexture.hpp>
#include <graphics/types/drawData.hpp>
#include <memory>
#include <object/particle.hpp>
#include <utility>

namespace Objects {

class Projectile {
    const int PARTICLE_CHANCE = 3; // Chance that a particle spawn

  public:
    Projectile(Graphics::AnimatedTexture*       texture,
               Graphics::BaseTexture*           effect,
               const SDL_FPoint&                startPosition,
               const double&                    angle,
               const int&                       duration,
               const float&                     velocity,
               const int&                       damage,
               const std::shared_ptr<Particle>& particle); // Constructor
    ~Projectile();

    SDL_FRect* getPosition(); // Returns a pointer to the current position
    [[nodiscard]] bool effectsEnabled() const;
    [[nodiscard]] int                          getNewDuration(); // Calculate and return the new duration
    [[nodiscard]] int                          getDamage() const;
    [[nodiscard]] Graphics::typeDrawData       getEffect();                 // Return draw data for lightning
    [[nodiscard]] Graphics::typeDrawDataAngled getProjectile();             // Return draw data for the projectile
    [[nodiscard]] SDL_FPoint                   getProjectileCenter() const; // Return the center for a projectile

    void move(); // All functions related to movement
  private:
  protected:
    const bool mParticleEnabled; // If particle was enabled
    const bool mEffectEnabled;

    Graphics::AnimatedTexture* pProjectile;       // Reference to animated texture
    Graphics::BaseTexture*     pEffect;           // Reference to the lightning, if it exists
    SDL_FRect                  mParticlePosition; // Current position of the projectile
    SDL_FPoint                 mParticleCenter;   // Center of particles
    SDL_FRect                  mEffectPosition;   // Current position of effect (if used)
    int                        mDamage;
    double                     mAngle;    // Rotation angle
    const float                mVelocity; // Velocity
    int                        mDuration; // Number of ticks, destroyed on 0
    std::shared_ptr<Particle>  mParticle; // Reference to the particle engine
};
}