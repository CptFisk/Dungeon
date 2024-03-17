#pragma once
#include <SDL3/SDL.h>
#include <common/scale.hpp>
#include <graphics/structures.hpp>

namespace Editor {
/**
 * @brief Generate a overlay that show the last type of the tile, also have a small counter in the top right
 * @brief corner that show how many texture is placed over each other
 */
class VisualTile {
  public:
    VisualTile() = default;
    VisualTile(const int& x, const int& y, Graphics::typeSimpleTexture number, const Common::typeScale& scale);

    void newOverlay(SDL_Texture* overlay); // Bind a new texture as overlay
    std::pair<SDL_Texture*, SDL_FRect> getOverlay();

    void resetCounter();     // Reset the counter
    void incrementCounter(); // Increment the counter

  protected:
  private:
    SDL_Texture* texture;  // Overlay texture
    SDL_FRect    position; // Overlay position

    Graphics::typeSimpleTexture numbers;
    SDL_FRect                   numbersPosition; // Position of numbers
    int                         counter;         // Current counter
};
}