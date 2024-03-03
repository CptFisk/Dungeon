#include <common/sdl.hpp>

namespace Common {
SDL_FRect
newSDL_FRect(const int& x, const int& y) {
    return newSDL_FRect(static_cast<float>(x), static_cast<float>(y));
}

SDL_FRect
newSDL_FRect(const float& x, const float& y) {
    return SDL_FRect{ x * 16.0f,
                      y * 16.0f,
                      16.0f,
                      16.0f};
}

}