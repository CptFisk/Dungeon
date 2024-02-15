#pragma once
#include <SDL3/SDL.h>
#include <vector>

namespace Objects{
class Particle{
    struct ParticleStruct{
        SDL_FRect Position;
        int Duration;
    };
  public:
    Particle();
    ~Particle();

    void draw();
  protected:
  private:
    std::vector<ParticleStruct> mParticles;
    SDL_Texture* mTexture;
};
}