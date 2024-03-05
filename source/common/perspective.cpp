#include <common/perspective.hpp>

namespace Common {
Perspective::Perspective(SDL_Renderer* renderer)
  : pRenderer(renderer)
  , mOffset{} {}

void
Perspective::render(SDL_Texture* texture, SDL_FRect* viewport, SDL_FRect* destination) {
    SDL_FRect dest = *destination;
    dest.x += mOffset.first;
    dest.y += mOffset.second;
    SDL_RenderTexture(pRenderer, texture, viewport, &dest);
}

void
Perspective::renderRotated(SDL_Texture* texture, SDL_FRect* viewport, SDL_FRect* destination, const float& angle) {
    SDL_RenderTextureRotated(pRenderer, texture, viewport, destination, angle, nullptr, SDL_FLIP_NONE);
}

void
Perspective::move(Directions direction, const float& velocity) {
    switch(direction){
        case NORTH:
            mOffset.second += velocity;
            break;
        case EAST:
            mOffset.first -= velocity;
            break;
        case SOUTH:
            mOffset.second -= velocity;
            break;
        case WEST:
            mOffset.first += velocity;
            break;
        default:
            break;
    }
}

}