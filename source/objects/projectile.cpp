#include <objects/projectile.hpp>
#include <utility/textures.hpp>
#include <utility/trigonometry.hpp>

namespace Objects {

Projectile::Projectile(const Objects::typeProjectileStruct& setup,
                       const std::pair<float, float>&        playerPosition,
                       const Common::typeScale&              scale,
                       SDL_Renderer*                        renderer,
                       std::shared_ptr<Particle>            particle)
  : pProjectile(setup.Projectile)
  , mParticle(particle)
  , pLightning(setup.Lightning)
  , pRenderer(renderer)
  , mDuration(setup.Duration)
  , mVelocity(setup.Velocity)
  , mAngle(setup.Angle)
  , mCurrentPosition{ playerPosition.first + (4.0f *scale.ScaleX),
                      playerPosition.second +(4.0f * scale.ScaleY),
                      8.0f * scale.ScaleX,
                      8.0f * scale.ScaleY }
  , mLightningPosition{ playerPosition.first + (((8.0f * scale.ScaleX) / 2) - ((16.0f * scale.ScaleX) / 2)),
                        playerPosition.second + (((8.0f * scale.ScaleY) / 2) - ((16.0f * scale.ScaleY) / 2)),
                        16.0f * scale.ScaleX,
                        16.0f * scale.ScaleY } {
    mParticleEnabled = particle != nullptr ? true : false;
}

Projectile::~Projectile() = default;

SDL_FRect*
Projectile::getPosition() {
    return &mCurrentPosition;
}

void
Projectile::draw() {
    if (mParticleEnabled && (rand() % PARTICLE_CHANCE == 1)) {
        mParticle->addParticle(mCurrentPosition);
    }

    if (pLightning != nullptr) {
        SDL_RenderTexture(pRenderer, pLightning, nullptr, &mLightningPosition);
    }

    SDL_RenderTextureRotated(
      pRenderer, pProjectile->getTexture(), pProjectile->getViewport(), &mCurrentPosition, mAngle, nullptr, SDL_FLIP_NONE);
    move();
}

void
Projectile::move() {
    // Move to new position
    auto delta = Utility::calculateVector(mAngle, mVelocity, mCurrentPosition.x, mCurrentPosition.y);

    mCurrentPosition.x += delta.first;
    mCurrentPosition.y += delta.second;
    mLightningPosition.x += delta.first;
    mLightningPosition.y += delta.second;
}

int
Projectile::getNewDuration() {
    return mDuration--;
}

}