#include <iostream>
#include <objects/projectile.hpp>
namespace Objects {

Projectile::Projectile(const Objects::ProjectileStruct& setup, SDL_Renderer* renderer)
  : pProjectile(setup.Projectile)
  , pLightning(setup.Lightning)
  , pRenderer(renderer)
  , mDuration(setup.Duration)
  , mCurrentPosition{ 100, 100, 18, 18 } {}

void
Projectile::draw() {
    SDL_FRect d = { 84, 84, 50, 50 };
    SDL_RenderTextureRotated(pRenderer,
                             pProjectile->getTexture(),
                             pProjectile->getViewport(),
                             &mCurrentPosition,
                             mAngle,
                             nullptr,
                             SDL_FLIP_NONE);
    if (pLightning != nullptr) {
        if (SDL_RenderTexture(pRenderer, pLightning, nullptr, &d) != 0)
            std::cout << SDL_GetError() << std::endl;
    }
    mAngle += 5;
}

}