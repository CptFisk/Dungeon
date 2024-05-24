#pragma once
#include <graphics/animatedTexture.hpp>

namespace Objects{

class Door{
  public:
    Door();
    ~Door();
  protected:
  private:
    Graphics::AnimatedTexture mGraphic;
};
}