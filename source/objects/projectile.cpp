#include <objects/projectile.hpp>

namespace Objects {
Projectile::Projectile(SDL_Texture* texture, SDL_Renderer* renderer)
  : mTexture(texture)
  , mRenderer(renderer) {}
}