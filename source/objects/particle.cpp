#include <objects/particle.hpp>

namespace Objects {
Particle::Particle(SDL_Texture* texture, SDL_Renderer* renderer, const int& duration, const float& size)
  : pTexture(texture)
  , pRenderer(renderer)
  , mDuration(duration)
  , mSize(size){}

Particle::~Particle() {}

void
Particle::addParticle(const float& x, const float& y) {
    mParticles.push_back(ParticleStruct{ SDL_FRect{ x, y, mSize, mSize }, mDuration });
}

void
Particle::draw() {
    for (auto it = mParticles.begin(); it != mParticles.end();) {
        if ((*it).Duration < 0) {
            it = mParticles.erase(it);

        } else {
            SDL_RenderTexture(pRenderer, pTexture, nullptr, &(*it).Position);
            (*it).Duration--; // Reduce duration
            ++it;
        }
    }
}

}