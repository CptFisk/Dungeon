#pragma once
#include <SDL3/SDL.h>
#include <cmake.hpp>
#include <common/scale.hpp>
#include <common/structures.hpp>
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
        SDL_FRect    Position;
    };

  public:
#ifdef GAME_MODE
    [[maybe_unused]] Tile(const int& x, const int& y); // Used during gameplay
#endif
#ifdef EDITOR_MODE
    [[maybe_unused]] Tile(const int& x, const int& y, const Common::typeScale& scale); // Used in editor mode
#endif
    ~Tile() = default;

    Tile& operator=(const Tile& other); // Operator overload

    [[maybe_unused]] void clear(); // Clear vector

#ifdef GAME_MODE
    [[maybe_unused]] void addData(SDL_Texture* texture, SDL_FRect viewport, const int& w, const int& h);     // Used during gameplay
    [[maybe_unused]] void addData(SDL_Texture* texture, SDL_FRect viewport, const float& w, const float& h); // Used during gameplay
#endif
#ifdef EDITOR_MODE
    [[maybe_unused]] void addData(SDL_Texture*            texture,
                                  SDL_FRect               viewport,
                                  const float&            w,
                                  const float&            h,
                                  const Common::typeScale scale); // Used in editor mode
#endif
    std::vector<Common::typeDrawData> getDrawData(); // Return all data that should be drawn.

  private:
  protected:
    const float           xPos;
    const float           yPos;
    std::vector<tileData> data; // All data that belongs to the tile. This is to allow multiple layers of texture to a base tile
};
}