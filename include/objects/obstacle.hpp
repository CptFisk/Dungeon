#pragma once
#include <graphics/structures.hpp>
namespace Objects{

class Obstacle{
  public:
    Obstacle(const Graphics::BaseTexture& base);
  protected:
  private:
    Graphics::BaseTexture mBase;
};
}