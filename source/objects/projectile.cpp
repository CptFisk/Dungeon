#include <objects/projectile.hpp>
#include <iostream>
namespace Objects {
struct ProjectileStruct{

};

Projectile::Projectile(Graphics::AnimatedTexture* texture, SDL_Renderer* renderer, SDL_Texture* lightning)
  : pProjectile(texture)
  , pLightning(lightning)
  , pRenderer(renderer)
  , mAngle(0.0) {
    mCurrentPosition = { 100, 100, 18, 18 };
}

void
Projectile::draw() {
    SDL_FRect d = {84,84, 50,50};
    SDL_RenderTextureRotated(
      pRenderer, pProjectile->getTexture(), pProjectile->getViewport(), &mCurrentPosition, mAngle, nullptr, SDL_FLIP_NONE);
    if(pLightning != nullptr) {
        if (SDL_RenderTexture(pRenderer, pLightning, nullptr, &d) != 0)
             std::cout << SDL_GetError() << std::endl;
    }
    mAngle += 5;
}

}