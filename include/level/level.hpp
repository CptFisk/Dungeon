#pragma once
#include <SDL3/SDL.h>
#include <common/structures.hpp>
#include <global.hpp>
#include <graphicsForward.hpp>
#include <level/file.hpp>
#include <level/tile.hpp>
#include <memory>
#include <string>
#include <vector>

namespace Level {

class Level {
  public:
    Level(SDL_Renderer* renderer, std::shared_ptr<Graphics::Graphics> graphics, Uint8& red, Uint8& green, Uint8& blue);
    ~Level(); // Cleaning

    void loadLevel(const std::string& filename);
    /**
     * @breif Check if movement is allowed, or if it collides with other objects
     * @param other Object to check with
     * @return true = movement allowed
     */
    bool movement(const SDL_FRect& other, const Directions& direction);

    std::vector<Common::typeDrawData> getLevel(); // Return all draw data

  protected:
  private:
    Uint8& red;   // Reference to engine->Background->Red
    Uint8& green; // Reference to engine->Background->Green
    Uint8& blue;  // Reference to engine->Background->Blue

    // Graphical stuff
    std::shared_ptr<Graphics::Graphics> mGraphics;
    SDL_Renderer*                       pRenderer; // Reference to the renderer

    std::vector<SDL_FRect> obstacles; // Things that you cant walk over
    std::vector<SDL_FRect> walls;
    // Level data
    File::typeHeader  header;
    std::vector<Tile> tiles;
    int               elements; // Number of elements that exist in pTiles
};

}