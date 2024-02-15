#pragma once
#include <SDL3/SDL.h>
#include <vector>

namespace Objects {
class Particle {
    struct ParticleStruct {
        SDL_FRect Position;
        int       Duration;
    };

  public:
    Particle(SDL_Texture* texture, SDL_Renderer* renderer, const int& duration, const float& size);
    ~Particle();

    void addParticle(const float& x, const float& y); // Position for particle
    void draw();                                      // Draw particles
  protected:
  private:
    int                         mDuration;  // Duration for particles
    float                       mSize;      // Size for all particles
    std::vector<ParticleStruct> mParticles; // Vector containing all particles
    SDL_Renderer*               pRenderer;
    SDL_Texture*                pTexture;

};
}