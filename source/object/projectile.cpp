#include <object/projectile.hpp>
#include <utility/textures.hpp>
#include <utility/trigonometry.hpp>

namespace Objects {

Projectile::Projectile(const Objects::typeProjectileStruct& setup,
                       const std::pair<float, float>&       playerPosition,
                       SDL_Renderer*                        renderer,
                       std::shared_ptr<Particle>            particle)
  : pProjectile(setup.Projectile)
  , mParticle(particle)
  , pLightning(setup.Lightning)
  , pRenderer(renderer)
  , mDuration(setup.Duration)
  , mVelocity(setup.Velocity)
  , mAngle(setup.Angle)
  , mDamage(50)
  , mCurrentPosition{ playerPosition.first + (4.0f), playerPosition.second + (4.0f), 8.0f, 8.0f }
  , mLightningPosition{ playerPosition.first + ((8.0f / 2.0f) - (16.0f / 2.0f)),
                        playerPosition.second + ((8.0f / 2.0f) - (16.0f / 2.0f)),
                        16.0f,
                        16.0f } {
    mParticleEnabled = particle != nullptr ? true : false;
}

Projectile::~Projectile() = default;

SDL_FRect*
Projectile::getPosition() {
    return &mCurrentPosition;
}

Common::typeDrawData
Projectile::getLightning() {
    return Common::typeDrawData{ pLightning, nullptr, &mLightningPosition };
}

Common::typeDrawDataAngled
Projectile::getProjectile() {
    if (mParticleEnabled && rand() % PARTICLE_CHANCE == 1)
        mParticle->addParticle(mCurrentPosition);
    return Common::typeDrawDataAngled{ pProjectile->getTexture(), pProjectile->getAnimatedViewport(), &mCurrentPosition, mAngle };
};

void
Projectile::move() {
    // Move to new position

    auto delta = Utility::calculateVector(mAngle, mVelocity);

    mCurrentPosition.x += delta.x;
    mCurrentPosition.y += delta.y;
    mLightningPosition.x += delta.x;
    mLightningPosition.y += delta.y;
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