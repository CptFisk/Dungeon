#include <objects/projectile.hpp>

namespace Objects {
Projectile::Projectile(const Graphics::BaseTexture& base, SDL_Renderer* renderer)
  : mTexture(base.Texture)
  , mRenderer(renderer)
  , mAngle(0.0) {
    mCurrentViewport = base.Views[0];
    mCurrentPosition = { 100, 100, 18, 18 };
}

void
Projectile::draw() {
    SDL_RenderTextureRotated(mRenderer, mTexture, &mCurrentViewport, &mCurrentPosition, mAngle, nullptr, SDL_FLIP_NONE);
    mAngle += 5;
}
}