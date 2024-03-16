#pragma once
#include <SDL3/SDL.h>
#include <common/scale.hpp>
#include <vector>
#include <common/structures.hpp>

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
    Tile() = default;
    [[maybe_unused]] Tile(const int& x, const int& y);                                 // Used during gameplay
    [[maybe_unused]] Tile(const int& x, const int& y, const Common::typeScale& scale); // Used in editor mode
    ~Tile() = default;

    [[maybe_unused]] void clear(); // Clear vector

    size_t addData(SDL_Texture* texture, const SDL_FRect& viewport); // Add element to the vector

    std::vector<Common::typeDrawData> getTile();    //Return all data that should be drawn.

  private:
  protected:
    SDL_FRect       position; // The position in the grid, the position never changes
    std::vector<tileData> data;     // All data that belongs to the tile. This is to allow multiple layers of texture to a base tile
};
}