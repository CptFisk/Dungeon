#include <objects/projectile.hpp>
#include <utility/trigonometry.hpp>

namespace Objects {

Projectile::Projectile(const Objects::ProjectileStruct& setup,
                       const std::pair<float, float>    playerPosition,
                       const Engine::Scale              scale,
                       SDL_Renderer*                    renderer)
  : pProjectile(setup.Projectile)
  , pLightning(setup.Lightning)
  , pRenderer(renderer)
  , mDuration(setup.Duration)
  , mVelocity(setup.Velocity)
  , mAngle(setup.Angle)
  , mCurrentPosition{ playerPosition.first, playerPosition.first, 8.0f * scale.ScaleX, 8.0f * scale.ScaleY }
  , mLightningPosition{ playerPosition.first + ((8.0f * scale.ScaleX) / 2) - ((16.0f * scale.ScaleX) / 2),
                        playerPosition.second + ((8.0f * scale.ScaleY) / 2) - ((16.0f * scale.ScaleY) / 2),
                        16.0f * scale.ScaleX,
                        16.0f * scale.ScaleY } {}

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