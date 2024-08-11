#pragma once
#include <SDL.h>
#include <graphics/types/drawData.hpp>
#include <random>
#include <vector>

namespace Objects {
class Particle {
    struct ParticleStruct {
        SDL_FRect Position;
        int       Duration;
    };

  public:
    Particle(SDL_Texture* texture, const int& duration, const float& size, const float& velocity);
    ~Particle();

    void                                addParticle(const SDL_FRect& position); // Position for particle
    std::vector<Graphics::typeDrawData> getDrawData();

  protected:
    void randomPosition(SDL_FRect& rect);

  private:
    const int                   duration; // Duration for particles
    const float                 velocity;
    const float                 size;      // Size for all particles
    std::vector<ParticleStruct> particles; // Vector containing all particles
    SDL_Texture*                texture;

    std::random_device                    rd;
    std::mt19937                          gen;
    std::uniform_real_distribution<float> distribution;
};
}