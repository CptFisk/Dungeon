#pragma once
#include <common/scale.hpp>
#include <SDL3/SDL.h>

namespace Player{
class Health{
  public:
    Health(bool& visible, int& health, Common::typeScale& scale);
  protected:
  private:
    const SDL_FRect mPosition;
    bool& mVisible;
    int& mHealth;
    Common::typeScale& mScale;
};
}