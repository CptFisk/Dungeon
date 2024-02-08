#include <objects/projectile.hpp>

namespace Objects {
Projectile::Projectile(Graphics::AnimatedTexture* texture, SDL_Renderer* renderer)
  : mTexture(texture)
  , mRenderer(renderer)
  , mAngle(0.0){
    mCurrentPosition = { 100, 100, 18, 18 };
}

void
Projectile::draw() {
    SDL_RenderTextureRotated(mRenderer, mTexture->getTexture(), mTexture->getViewport(), &mCurrentPosition, 0, nullptr, SDL_FLIP_NONE);
    mAngle += 5;
}


}