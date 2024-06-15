#pragma once
#include <SDL.h>
#include <common/scale.hpp>
#include <global.hpp>

namespace Common {
class Perspective {
  public:
    Perspective(SDL_Renderer* renderer, float& offsetX, float& offsetY, SDL_FPoint& playerCenter);

    void render(SDL_Texture* texture, const SDL_Rect* viewport, SDL_FRect* position);
    void renderRotated(SDL_Texture* texture,const SDL_Rect* viewport, SDL_FRect* position, const float& angle);

    void move(Directions direction, const float& velocity); // Move the camera
    void center(const float& x, const float& y);

    struct {
        float& x;
        float& y;
    } mOffset;

  private:
  protected:
    SDL_Renderer*               pRenderer;
    [[maybe_unused]] SDL_FPoint& pPlayerCenter; // Only used during "game-mode"

    static constexpr float halfX = static_cast<float>((16*16)/2);
    static constexpr float halfY = static_cast<float>((12*16)/2);
};
}