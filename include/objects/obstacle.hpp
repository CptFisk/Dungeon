#pragma once
#include <graphics/structures.hpp>
namespace Objects {

class Obstacle {
  public:
    Obstacle(const Graphics::BaseTexture& base, const SDL_FRect& position);
    std::tuple<SDL_Texture*, SDL_FRect, SDL_FRect > getObstacle() const;

  protected:
  private:
    Graphics::BaseTexture mBase;
    SDL_FRect             mObstaclePosition;
    SDL_FRect             mViewport; // The viewport we decide to use
};
}