#include <common/perspective.hpp>

namespace Common {
Perspective::Perspective(SDL_Renderer* renderer)
  : pRenderer(renderer) {}

void
Perspective::render(SDL_Texture* texture, SDL_FRect *viewport, SDL_FRect* destination) {
    SDL_FRect dest = *destination;
    SDL_RenderTexture(pRenderer, texture, viewport, &dest);
}

void
Perspective::renderRotated(SDL_Texture* texture, SDL_FRect* viewport, SDL_FRect* destination, const float& angle) {

}
}