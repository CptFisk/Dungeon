#pragma once
#include <SDL.h>
#include <cmake.hpp>
#include <common/scale.hpp>
#include <common/structures.hpp>
#include <graphicsForward.hpp>
#include <graphics/structures.hpp>
#include <vector>
namespace Editor {
/**
 * @brief Internal structure for the visibility of a tile
 */
struct tileData {
    SDL_Texture* Texture;
    SDL_Rect*    Viewport;
    SDL_FRect    Position;
};

/**
 * @brief Basic class to hold all the data related to a tile. It will hold position and all the different textures.
 */
class Tile {
  public:
    Tile(const int& x, const int& y, const Common::typeScale& scale); // Used in editor mode
    ~Tile() = default;

    Tile& operator=(const Tile& other); // Operator overload

    [[maybe_unused]] void clear(); // Clear vector

    void addData(const std::string& asset,const std::shared_ptr<Graphics::Graphics>& graphics); // Used in editor mode

    std::vector<Common::typeDrawData> getDrawData(); // Return all data that should be drawn.
    std::vector<tileData>&            getTileData(); // Return a reference to data
  private:
  protected:
    const float           xPos;
    const float           yPos;
    const Common::typeScale scale;
    std::vector<tileData> data; // All data that belongs to the tile. This is to allow multiple layers of texture to a base tile
};
}