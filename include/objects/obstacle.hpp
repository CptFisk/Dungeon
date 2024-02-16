#pragma once
#include <graphics/structures.hpp>
namespace Objects {

class Obstacle {
  public:
    Obstacle(const Graphics::BaseTexture& base);
    std::pair<SDL_Texture*, SDL_FRect> getObstacle() const;
  protected:
  private:
    Graphics::BaseTexture mBase;
    SDL_FRect             mViewport; // The viewport we decide to use
};
}