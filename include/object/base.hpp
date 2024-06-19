#pragma once
#include <SDL.h>

namespace Objects {
class Base {
  public:

    Base(const SDL_FRect& position)
      : mPosition(position) {}
    virtual ~Base() {}

    SDL_FRect& getPosition() { return mPosition; }

  protected:
  private:
    SDL_FRect mPosition;
};

}