#pragma once
#include <graphics/types/simpleTexture.hpp>
namespace Objects {

class Obstacle {
  public:
    Obstacle(const Graphics::typeSimpleTexture& base, const SDL_FRect& position);
    std::tuple<SDL_Texture*, SDL_FRect, SDL_FRect > getObstacle() const;

  protected:
  private:
    Graphics::typeSimpleTexture mBase;
    SDL_FRect             mObstaclePosition;
    SDL_FRect             mViewport; // The viewport we decide to use
};
}