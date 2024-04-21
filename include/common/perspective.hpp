#pragma once
#include <SDL3/SDL.h>
#include <common/scale.hpp>
#include <global.hpp>

namespace Common {
class Perspective {
  public:
    Perspective(SDL_Renderer* renderer, float& offsetX, float& offsetY, SDL_Point* playerCenter = nullptr);

    void render(SDL_Texture* texture, SDL_FRect* viewport, SDL_FRect* position);
    void renderRotated(SDL_Texture* texture, SDL_FRect* viewport, SDL_FRect* position, const float& angle);

    void move(Directions direction, const float& velocity); // Move the camera
    void center(const float& x, const float& y);

    struct {
        float& x;
        float& y;
    } mOffset;

  private:
  protected:
    SDL_Renderer*               pRenderer;
    [[maybe_unused]] SDL_Point* pPlayerCenter; // Only used during "game-mode"
};
}