#pragma once
#include <SDL3/SDL.h>
#include <common/scale.hpp>
#include <utility>

namespace Common {
class Perspective {
  public:
    Perspective(SDL_Renderer* renderer);

    void render(SDL_Texture* texture, SDL_FRect* viewport, SDL_FRect destination);

  private:
  protected:
    std::pair<float, float> mOffset;
    typeScale               mScale; // Current scale

    SDL_Renderer* pRenderer;
};
}