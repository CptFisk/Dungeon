#include <common/sdl.hpp>

namespace Common {
SDL_FRect
newSDL_FRect(const int& x, const int& y, const typeScale& scale) {
    return newSDL_FRect(static_cast<float>(x), static_cast<float>(y), scale);
}

SDL_FRect
newSDL_FRect(const float& x, const float& y, const typeScale& scale) {
    return SDL_FRect{ x * 16.0f * static_cast<float>(scale.ScaleX),
                      y * 16.0f * static_cast<float>(scale.ScaleY),
                      16.0f * scale.ScaleX,
                      16.0f * scale.ScaleY };
}

}