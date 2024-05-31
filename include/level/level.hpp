#pragma once
#include <SDL.h>
#include <common/structures.hpp>
#include <global.hpp>
#include <graphicsForward.hpp>
#include <level/file.hpp>
#include <memory>
#include <objects/door.hpp>
#include <string>
#include <vector>

namespace Level {

class Level {
  public:
    Level(SDL_Renderer*                       renderer,
          std::shared_ptr<Graphics::Graphics> graphics,
          Uint8&                              red,
          Uint8&                              green,
          Uint8&                              blue);
    ~Level(); // Cleaning
    void loadLevel(const std::string& filename);
    /**
     * @breif Check if movement is allowed, or if it collides with other objects
     * @param other Object to check with
     * @return true = movement allowed
     */
    bool movement(const SDL_FRect& other, const Directions& direction);
    bool movement(const SDL_FPoint& other, const Directions& direction);

    /**
     * @brief Returns the position were the player should spawn
     */
    std::pair<uint8_t, uint8_t> getPlayerSpawn();

    std::vector<Common::typeDrawData>               getLevel(); // Return all draw data

    void interact(const SDL_FRect& area);
  protected:
    /**
     * @brief Split the graphic into smaller chunks and then generate graphics on them instead.
     * @brief Resulting that instead of having 128x 128 pixels you only have a grid 6x 6 instead.
     */
    void   createSegments();
    void   addToSegment(const int& pos, const std::string& name);
    size_t getSegment(const std::pair<int, int> coord) const;

    inline void clearDoors();

    std::vector<std::pair<SDL_FRect, SDL_Texture*>> mSegments;  // Level segments (generated)

  private:
    Uint8& red;   // Reference to engine->Background->Red
    Uint8& green; // Reference to engine->Background->Green
    Uint8& blue;  // Reference to engine->Background->Blue

    // Graphical stuff
    std::shared_ptr<Graphics::Graphics> mGraphics;
    SDL_Renderer*                       pRenderer; // Reference to the renderer


    std::vector<SDL_FRect>     obstacles; // Things that you cant walk over
    std::vector<SDL_FRect>     walls;
    std::vector<Objects::Door*> doors;   //All doors on the map
    // Level data
    File::typeHeader header;
    int              elements; // Number of elements that exist in pTiles

    static const int segmentSizeX = 64;
    static const int segmentSizeY = 64;
};

}