#include <objects/obstacle.hpp>

namespace Objects {
Obstacle::Obstacle(const Graphics::BaseTexture& base, const SDL_FRect& position)
  : mBase(base)
  , mObstaclePosition(position){};

std::tuple<SDL_Texture*, SDL_FRect, SDL_FRect>
Obstacle::getObstacle() const {
    return { mBase[0].first, mBase[0].second, mObstaclePosition };
}
}