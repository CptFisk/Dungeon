#include <common/scale.hpp>
#include <error.hpp>
namespace Common {
void
calculateGameScale(typeScale& scale, SDL_Window* window) {
    int   width, height;
    float factorX, factorY; // Internal variables
    SDL_GetWindowSizeInPixels(window, &width, &height);
    const float squaresX  = 16.0; // Numbers of square in x-direction
    const float squareY   = 12.0; // Numbers of square in y-direction
    const float pixelSize = 16.0;
    factorX               = (static_cast<float>(width) / squaresX) / pixelSize;
    factorY               = (static_cast<float>(height) / squareY) / pixelSize;
    scale.windowWidth     = width;
    scale.windowWidthF    = static_cast<float>(width);
    scale.windowHeight    = height;
    scale.windowHeightF   = static_cast<float>(height);

    scale.selectedScale = std::ceil(std::min(factorX, factorY)); // Selecting the smallest value

    if (factorX == factorY) {
        scale.factorX = 1.0f;
        scale.factorY = 1.0f;
    } else if (factorX > factorY) {
        scale.factorX = factorX / factorY;
        scale.factorY = 1.0f;
    } else if (factorY > factorX) {
        scale.factorX = 1.0f;
        scale.factorY = factorY / factorX;
    } else {
        ASSERT_WITH_MESSAGE(true, "Cant calculate scale value");
    }
}
}