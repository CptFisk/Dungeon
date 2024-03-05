#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <random>

namespace Objects {
class Particle {
    struct ParticleStruct {
        SDL_FRect Position;
        int       Duration;
    };

  public:
    Particle(SDL_Texture* texture, SDL_Renderer* renderer, const int& duration, const float& size, const float& velocity);
    ~Particle();

    void addParticle(const SDL_FRect& position); // Position for particle
    void draw();                                 // Draw particles
  protected:
    void randomPosition(SDL_FRect& rect);

  private:
    const int                   mDuration; // Duration for particles
    const float                 mVelocity;
    const float                 mSize;      // Size for all particles
    std::vector<ParticleStruct> mParticles; // Vector containing all particles
    SDL_Renderer*               pRenderer;
    SDL_Texture*                pTexture;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> mDist;
};
}