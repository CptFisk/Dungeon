#include <common/scale.hpp>

namespace Common {
void
calculateGameScale(Scale& scale, SDL_Window* window) {
    int width, height;
    SDL_GetWindowSizeInPixels(window, &width, &height);
    const float squaresX  = 16.0; // Numbers of square in x-direction
    const float squareY   = 12.0; // Numbers of square in y-direction
    const float pixelSize = 16.0;
    scale.ScaleX          = (static_cast<float>(width) / squaresX) / pixelSize;
    scale.ScaleY          = (static_cast<float>(height) / squareY) / pixelSize;
    scale.WindowX         = width;
    scale.WindowY         = height;
}
}