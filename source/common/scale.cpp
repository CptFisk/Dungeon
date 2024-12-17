#include <common/scale.hpp>
#include <error.hpp>
#include <global.hpp>
namespace Common {
void
calculateGameScale(typeScale& scale, SDL_Window* window) {
    int   width, height;
    float factorX, factorY; // Internal variables
    SDL_GetWindowSizeInPixels(window, &width, &height);
    const auto squaresX  = static_cast<float>(BLOCKS_WIDTH);  // Numbers of square in x-direction
    const auto squareY   = static_cast<float>(BLOCKS_HEIGHT); // Numbers of square in y-direction
    const auto pixelSize = static_cast<float>(PIXEL_SIZE);
    factorX              = (static_cast<float>(width) / squaresX) / pixelSize;
    factorY              = (static_cast<float>(height) / squareY) / pixelSize;
    scale.windowWidth    = width;
    scale.windowWidthF   = static_cast<float>(width);
    scale.windowHeight   = height;
    scale.windowHeightF  = static_cast<float>(height);

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