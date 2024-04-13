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

SDL_FRect
newSDL_FRectScaled(const int& x, const int&y, const typeScale& scale){
    return newSDL_FRectScaled(static_cast<float>(x), static_cast<float>(y), scale);
}

SDL_FRect
newSDL_FRectScaled(const float& x, const float&y, const typeScale& scale){
    return SDL_FRect{ x * 16.0f * static_cast<float>(scale.factorX),
                      y * 16.0f * static_cast<float>(scale.factorY),
                      16.0f * scale.factorX,
                      16.0f * scale.factorY };
}

}