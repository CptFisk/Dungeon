#pragma once
#include <SDL3/SDL.h>
#include <level/structures.hpp>
#include <string>
#include <vector>
#include <common/scale.hpp>

namespace Level {
class Level {
  public:
    Level(SDL_Renderer* renderer,const Common::typeScale &scale);
    ~Level(); // Cleaning

    void loadLevel(const std::string& filename);
    bool movement(const SDL_FRect& other); // Check if movement is allowed, or if it collides with other objects

  protected:
  private:
    Common::typeScale mScale;
    SDL_Renderer*          pRenderer; // Reference to the renderer
    typeTile**             pTiles;
    std::vector<SDL_FRect> mObstacle; // Things that you cant walk over

    typeHeader mHeader;
};

}