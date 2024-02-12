#include <objects/projectile.hpp>
#include <utility/trigonometry.hpp>

namespace Objects {

Projectile::Projectile(const Objects::ProjectileStruct& setup, SDL_Renderer* renderer)
  : pProjectile(setup.Projectile)
  , pLightning(setup.Lightning)
  , pRenderer(renderer)
  , mDuration(setup.Duration)
  , mVelocity(setup.Velocity)
  , mAngle(setup.Angle)
  , mCurrentPosition{ 100, 100, 18, 18 }
  , mLightningPosition{ 84, 84, 50, 50 } {}

Projectile::~Projectile() {}

void
Projectile::draw() {
    SDL_RenderTextureRotated(pRenderer,
                             pProjectile->getTexture(),
                             pProjectile->getViewport(),
                             &mCurrentPosition,
                             mAngle,
                             nullptr,
                             SDL_FLIP_NONE);
    if (pLightning != nullptr) {
        SDL_RenderTexture(pRenderer, pLightning, nullptr, &mLightningPosition);
    }
    move();

}

void
Projectile::move() {
    // Move to new position
    float deltaX;
    float deltaY;
    Utility::calculateVector(mAngle, mVelocity, deltaX, deltaY);

    mCurrentPosition.x += deltaX;
    mCurrentPosition.y += deltaY;
    mLightningPosition.x += deltaX;
    mLightningPosition.y += deltaY;
}

int
Projectile::getNewDuration() {
    return mDuration--;
}

}