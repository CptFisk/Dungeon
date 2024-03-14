#pragma once
#include <SDL3/SDL.h>
#include <common/scale.hpp>
#include <vector>

namespace Level {
/**
 * @brief Basic class to hold all the data related to a tile. It will hold position and all the different textures.
 */
class Tile {
    /**
     * @brief Internal structure for the visibility of a tile
     */
    struct tileData {
        SDL_Texture* Texture;
        SDL_FRect    Viewport;
    };

  public:
    [[maybe_unused]] Tile(const float& x, const float& y);                                 // Used during gameplay
    [[maybe_unused]] Tile(const float& x, const float& y, const Common::typeScale& scale); // Used in editor mode

    [[maybe_unused]] void clear(); // Clear vector
    size_t                addData(SDL_Texture* texture, const SDL_FRect& viewport);

  private:
  protected:
    const SDL_FRect       position; // The position in the grid, the position never changes
    std::vector<tileData> data;     // All data that belongs to the tile. This is to allow multiple layers of texture to a base tile
};
}