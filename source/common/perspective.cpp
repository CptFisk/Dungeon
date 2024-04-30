#include <cmake.hpp>
#include <common/perspective.hpp>

namespace Common {
Perspective::Perspective(SDL_Renderer* renderer, float& offsetX, float& offsetY, SDL_FPoint* playerCenter)
  : pRenderer(renderer)
  , mOffset{ offsetX, offsetY }
  , pPlayerCenter(playerCenter) {}

void
Perspective::render(SDL_Texture* texture, SDL_FRect* viewport, SDL_FRect* position) {
    SDL_FRect pos = *position;
    pos.x += mOffset.x;
    pos.y += mOffset.y;
    SDL_RenderTexture(pRenderer, texture, viewport, &pos);
}

void
Perspective::renderRotated(SDL_Texture* texture, SDL_FRect* viewport, SDL_FRect* position, const float& angle) {
    SDL_FRect pos = *position;
    pos.x += mOffset.x;
    pos.y += mOffset.y;
    SDL_RenderTextureRotated(pRenderer, texture, viewport, &pos, angle, nullptr, SDL_FLIP_NONE);
}

void
Perspective::move(Directions direction, const float& velocity) {
    switch (direction) {
        case NORTH:
#ifdef GAME_MODE
            if (mOffset.y < 0)
#endif
#ifdef EDITOR_MODE
            if(mOffset.y < 0)
#endif
                mOffset.y += velocity;
            break;
        case EAST:
#ifdef GAME_MODE
            if(mOffset.x <= 0 && pPlayerCenter->x > halfX)
#endif
#ifdef EDITOR_MODE

#endif
            mOffset.x -= velocity;
            break;
        case SOUTH:
#ifdef GAME_MODE
            if (mOffset.y <= 0 && pPlayerCenter->y > halfY)
#else
            if (mOffset.y <= 0)
#endif
                mOffset.y -= velocity;
            break;
        case WEST:
#ifdef GAME_MODE
        if(mOffset.x < 0)
#else
          if(mOffset.x < 0)
#endif
            mOffset.x += velocity;
            break;
        default:
            break;
    }
}

void
Perspective::center(const float& x, const float& y) {
    // First we calculate what is the center of the screen
    constexpr auto centerX = 8 * 16; // Half the screen (16 block in width, each block is 16*16 pixels)
    constexpr auto centerY = 6 * 16; // Half the screen (12 block in height, each block is 16*16 pixels)

    mOffset.x = std::min(0.0f, centerX - x);
    mOffset.y = std::min(0.0f, centerY - y);
}

}