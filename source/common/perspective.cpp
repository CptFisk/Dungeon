#include <common/perspective.hpp>

namespace Common {
Perspective::Perspective(SDL_Renderer* renderer)
  : pRenderer(renderer)
  , mOffset{0.0f,0.0f} {}

void
Perspective::render(SDL_Texture* texture, SDL_FRect* viewport, SDL_FRect* position) {
    SDL_FRect dest = *position;
    dest.x += mOffset.x;
    dest.y += mOffset.y;
    SDL_RenderTexture(pRenderer, texture, viewport, &dest);
}

void
Perspective::renderRotated(SDL_Texture* texture, SDL_FRect* viewport, SDL_FRect* position, const float& angle) {
    SDL_RenderTextureRotated(pRenderer, texture, viewport, position, angle, nullptr, SDL_FLIP_NONE);
}

void
Perspective::move(Directions direction, const float& velocity) {
    switch(direction){
        case NORTH:
            mOffset.y += velocity;
            break;
        case EAST:
            mOffset.x -= velocity;
            break;
        case SOUTH:
            mOffset.y -= velocity;
            break;
        case WEST:
            mOffset.x += velocity;
            break;
        default:
            break;
    }
}

void
Perspective::center(const float& x, const float& y) {
    mOffset.x = x;
    mOffset.y = y;
}

}