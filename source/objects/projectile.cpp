#include <objects/projectile.hpp>

namespace Objects {
Projectile::Projectile(const Graphics::BaseTexture& base, SDL_Renderer* renderer)
  : mTexture(base.Texture)
  , mRenderer(renderer) {
    mCurrentViewport = base.Views[0];
    mCurrentPosition = {100,100,18,18};
}

void
Projectile::draw() {
    SDL_RenderTexture(mRenderer, mTexture, &mCurrentViewport, &mCurrentPosition);
}
}