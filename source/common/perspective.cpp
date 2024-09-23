#include <common/perspective.hpp>

namespace Common {
#ifdef GAME_MODE
Perspective::Perspective(SDL_Renderer*& renderer, float& offsetX, float& offsetY, SDL_FPoint& playerCenter, Common::typeScale& scale)
  : pRenderer(renderer)
  , mOffset{ offsetX, offsetY }
  , mPlayerCenter(playerCenter)
  , mScale(scale)
  , halfX{}
  , halfY{} {
    updateScale();
}
#endif

#ifdef EDITOR_MODE
Perspective::Perspective(SDL_Renderer*& renderer, float& offsetX, float& offsetY, Common::typeScale& scale)
  : pRenderer(renderer)
  , mScale(scale)
  , mOffset{ offsetX, offsetY } {}
#endif

void
Perspective::updateScale() {
    halfX = (256 * mScale.factorX) / 2.0f;
    halfY = (192 * mScale.factorY) / 2.0f;
}

void
Perspective::render(SDL_Texture* texture, const SDL_Rect* viewport, SDL_FRect* position) {
    SDL_FRect pos = *position;
    pos.x += mOffset.x;
    pos.y += mOffset.y;
    SDL_RenderCopyF(pRenderer, texture, viewport, &pos);
}

void
Perspective::renderRotated(SDL_Texture* texture, const SDL_Rect* viewport, SDL_FRect* position, const double& angle) {
    SDL_FRect pos = *position;
    pos.x += mOffset.x;
    pos.y += mOffset.y;
    SDL_RenderCopyExF(pRenderer, texture, viewport, &pos, angle, nullptr, SDL_FLIP_NONE);
}

#ifdef GAME_MODE
void
Perspective::move(Directions direction, const float& velocity) {
    switch (direction) {
        case NORTH:
            if (mOffset.y < 0)
                mOffset.y += velocity;
            break;
        case EAST:
            if (mOffset.x <= 0 && mPlayerCenter.x > halfX)
                mOffset.x -= velocity;
            break;
        case SOUTH:
            if (mOffset.y <= 0 && mPlayerCenter.y > halfY)
                mOffset.y -= velocity;
            break;
        case WEST:
            if (mOffset.x < 0)
                mOffset.x += velocity;
            break;
        default:
            break;
    }
}
#endif
#ifdef EDITOR_MODE
void
Perspective::move(Directions direction, const float& velocity) {
    switch (direction) {
        case NORTH:
            if (mOffset.y < 0)
                mOffset.y += velocity;
            break;
        case EAST:
            if (mOffset.x <= 0)
                mOffset.x -= velocity;
            break;
        case SOUTH:
            if (mOffset.y <= 0)
                mOffset.y -= velocity;
            break;
        case WEST:
            if (mOffset.x < 0)
                mOffset.x += velocity;
            break;
        default:
            break;
    }
}
#endif


void
Perspective::center(const SDL_FPoint& point, const float& offset) {
    center(point.x + offset, point.y + offset);
}

void
Perspective::center(const float& x, const float& y) {
    // First we calculate what is the center of the screen
    const auto centerX = 8 * 16 * mScale.factorX; // Half the screen (16 block in width, each block is 16*16 pixels)
    const auto centerY = 6 * 16 * mScale.factorY; // Half the screen (12 block in height, each block is 16*16 pixels)

    mOffset.x = std::min(0.0f, centerX - x);
    mOffset.y = std::min(0.0f, centerY - y);
}

}