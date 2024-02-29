#include <cstdlib>
#include <objects/particle.hpp>

namespace Objects {
Particle::Particle(SDL_Texture*  texture,
                   SDL_Renderer* renderer,
                   const int&    duration,
                   const float&  size,
                   const int&    velocity)
  : pTexture(texture)
  , pRenderer(renderer)
  , mDuration(duration)
  , mVelocity(velocity)
  , mSize(size) {}

Particle::~Particle() {
    mParticles.clear();
}

void
Particle::addParticle(const SDL_FRect& position) {
    const auto x = position.x + (position.w / 2.0f);
    const auto y = position.y + (position.h / 2.0f);
    mParticles.push_back(ParticleStruct{ SDL_FRect{ x, y, mSize, mSize }, mDuration });
}

void
Particle::draw() {
    for (auto it = mParticles.begin(); it != mParticles.end();) {
        if ((*it).Duration < 0) {
            it = mParticles.erase(it);

        } else {
            SDL_RenderTexture(pRenderer, pTexture, nullptr, &(*it).Position);
            randomPosition((*it).Position); // I LIKE TO MOVE IT MOVE IT
            (*it).Duration--;               // Reduce duration
            ++it;
        }
    }
}

void
Particle::randomPosition(SDL_FRect& rect) {
    auto x = std::rand() % mVelocity - (mVelocity / 2);
    auto y = std::rand() % mVelocity - (mVelocity / 2);
    rect.x += x;
    rect.y += y;
}

}