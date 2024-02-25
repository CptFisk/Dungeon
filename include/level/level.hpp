#pragma once
#include <SDL3/SDL.h>
#include <common/scale.hpp>
#include <graphicsForward.hpp>
#include <level/structures.hpp>
#include <memory>
#include <string>
#include <vector>
#include <global.hpp>

namespace Level {
class Level {
  public:
    Level(SDL_Renderer* renderer, const Common::typeScale& scale, std::shared_ptr<Graphics::Graphics> graphics);
    ~Level(); // Cleaning

    void loadLevel(const std::string& filename);
    /**
     * @breif Check if movement is allowed, or if it collides with other objects
     * @param other Object to check with
     * @return true = movement allowed
     */
    bool movement(const SDL_FRect& other, const Directions& direction);

    void draw();

  protected:
  private:
    // Graphical stuff
    std::shared_ptr<Graphics::Graphics> mGraphics;
    Common::typeScale                   mScale;
    SDL_Renderer*                       pRenderer; // Reference to the renderer

    std::vector<SDL_FRect> mObstacle; // Things that you cant walk over

    // Level data
    typeHeader mHeader;
    typeTile** pTiles;
    int        mElements;   //Number of elements that exist in pTiles
};

}