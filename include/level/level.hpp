#pragma once
#include <SDL3/SDL.h>
#include <common/structures.hpp>
#include <global.hpp>
#include <graphicsForward.hpp>
#include <level/file.hpp>
#include <memory>
#include <string>
#include <vector>

namespace Level {

class Level {
  public:
    Level(SDL_Renderer*                       renderer,
          std::shared_ptr<Graphics::Graphics> graphics,
          Uint8&                              red,
          Uint8&                              green,
          Uint8&                              blue,
          float&                              playerX,
          float&                              playerY);
    ~Level() = default; // Cleaning

    SDL_Texture* mLevel; // The complete level, but as one big sprite

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

    std::vector<Common::typeDrawData> getLevel(); // Return all draw data

  protected:
    /**
     * @brief Split the graphic into smaller chunks and then generate graphics on them instead.
     * @brief Resulting that instead of having 128x 128 pixels you only have a grid 6x 6 instead.
     */
    void createSegments();
    void addToSegment(const int& pos, const std::string& name);
    size_t getSegment(const std::pair<int,int> coord);

  private:
    Uint8& red;   // Reference to engine->Background->Red
    Uint8& green; // Reference to engine->Background->Green
    Uint8& blue;  // Reference to engine->Background->Blue

    // Graphical stuff
    std::shared_ptr<Graphics::Graphics> mGraphics;
    SDL_Renderer*                       pRenderer; // Reference to the renderer

    std::vector<std::pair<SDL_FRect, SDL_Texture*>> mSegments; // Level segments (generated)
    std::vector<SDL_FRect>                          obstacles; // Things that you cant walk over
    std::vector<SDL_FRect>                          walls;

    // Level data
    File::typeHeader header;
    int              elements; // Number of elements that exist in pTiles

    float& playerX; // Player position X-axis
    float& playerY; // Player position Y-axis

    static const int segmentSizeX = 25;
    static const int segmentSizeY = 25;
};

}