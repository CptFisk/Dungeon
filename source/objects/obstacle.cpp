#include <objects/obstacle.hpp>

namespace Objects {
Obstacle::Obstacle(const Graphics::BaseTexture& base)
  : mBase(base){};

std::pair<SDL_Texture*, SDL_FRect> Obstacle::getObstacle() const{
    return mBase[0];
}
}