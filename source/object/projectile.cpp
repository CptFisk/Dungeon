#include <object/projectile.hpp>
#include <utility/trigonometry.hpp>

namespace Objects {

Projectile::Projectile(Graphics::AnimatedTexture*       texture,
                       Graphics::BaseTexture*           effect,
                       const SDL_FPoint&                startPosition,
                       const double&                    angle,
                       const int&                       duration,
                       const float&                     velocity,
                       const int&                       damage,
                       const std::shared_ptr<Particle>& particle)
  : pProjectile(texture)
  , mParticle(particle)
  , pEffect(effect)
  , mDuration(duration)
  , mVelocity(velocity)
  , mAngle(angle)
  , mDamage(damage)
  , mParticleCenter(startPosition)
  , mParticleEnabled(particle != nullptr ? true : false)
  , mEffectEnabled(effect != nullptr ? true : false)
  // Set up the position dynamically
  , mParticlePosition{ startPosition.x - (texture->getWidthF() / 2.0f),
                       startPosition.y - (texture->getHeightF() / 2.0f),
                       texture->getWidthF(),
                       texture->getHeightF() }
  , mEffectPosition{ startPosition.x + ((8.0f / 2.0f) - (16.0f / 2.0f)),
                     startPosition.y + ((8.0f / 2.0f) - (16.0f / 2.0f)),
                     16.0f,
                     16.0f } {}

Projectile::~Projectile() = default;

SDL_FRect*
Projectile::getPosition() {
    return &mParticlePosition;
}

Graphics::typeDrawData
Projectile::getEffect() {
    return Graphics::typeDrawData{ pEffect->getTexture(), nullptr, &mEffectPosition };
}

Graphics::typeDrawDataAngled
Projectile::getProjectile() {
    if (mParticleEnabled && rand() % PARTICLE_CHANCE == 1)
        mParticle->addParticle(mParticlePosition);
    return Graphics::typeDrawDataAngled{ pProjectile->getTexture(), pProjectile->getAnimatedViewport(), &mParticlePosition, mAngle };
};

SDL_FPoint
Projectile::getProjectileCenter() const {
    return mParticleCenter;
}

void
Projectile::move() {
    // Move to new position
    auto delta = Utility::calculateVector(mAngle, mVelocity);
    mParticlePosition.x += delta.x;
    mParticlePosition.y += delta.y;

    mParticleCenter.x += delta.x;
    mParticleCenter.y += delta.y;

    mEffectPosition.x += delta.x;
    mEffectPosition.y += delta.y;
}

bool
Projectile::effectsEnabled() const {
    return mEffectEnabled;
}

int
Projectile::getNewDuration() {
    return mDuration--;
}

int
Projectile::getDamage() const {
    return mDamage;
}

}