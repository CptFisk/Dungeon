#include "utility/textures.hpp"

namespace Utility{

std::pair<float,float> getFRectCenter(const SDL_FRect& rect) {
    return std::pair<float,float>(rect.x + (rect.w / 2.0), rect.y + (rect.h / 2));
}
}