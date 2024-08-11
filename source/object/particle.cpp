#include <cstdlib>
#include <object/particle.hpp>

namespace Objects {
Particle::Particle(SDL_Texture* texture, const int& duration, const float& size, const float& velocity)
  : texture(texture)
  , duration(duration)
  , velocity(velocity)
  , size(size)
  , gen(rd())
  , distribution(-size, size) {}

Particle::~Particle() {
    particles.clear();
}

void
Particle::addParticle(const SDL_FRect& position) {
    const auto x = position.x + (position.w / 2.0f);
    const auto y = position.y + (position.h / 2.0f);
    particles.push_back(ParticleStruct{ SDL_FRect{ x, y, size, size }, duration });
}

std::vector<Graphics::typeDrawData>
Particle::getDrawData() {
    std::vector<Graphics::typeDrawData> data;
    for (auto it = particles.begin(); it != particles.end();) {
        if ((*it).Duration < 0) {
            it = particles.erase(it);

        } else {
            data.emplace_back(texture, nullptr, &(*it).Position);
            randomPosition((*it).Position); // Move it around
            (*it).Duration--;               // Reduce duration
            ++it;
        }
    }
    return data;
}

void
Particle::randomPosition(SDL_FRect& rect) {
    auto x = distribution(gen);
    auto y = distribution(gen);
    rect.x += x;
    rect.y += y;
}

}