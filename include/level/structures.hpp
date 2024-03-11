#pragma once
#include <SDL3/SDL.h>
#include <cstdint>
#include <string>
#include <vector>
#include <optional>

namespace Level {

const int TEXT_MAX_LENGTH      = 31;
const int MAX_ASSETS = 31;
const int TILE_TYPE_VARIATIONS = 7;

enum TileType : uint8_t { BLANK = 0, TEXTURE = 1 << 0, WALL = 1 << 1, OBSTACLE = 1 << 2 };
// Used inside data-file
struct typeTileData {
    uint8_t Type; // Tiletype
    uint8_t  Id;   // ID used in SubMetaFiles
};

struct typeTile {
    TileType     Type;     // Tiletype
    SDL_FRect    Position; // Position
    SDL_Texture* Texture;  // Reference to texture
    SDL_FRect    Viewport; // Viewport
    typeTile(TileType type, SDL_FRect position, std::pair<SDL_Texture*, SDL_FRect> texture)
      : Type(type)
      , Position(position)
      , Texture(texture.first)
      , Viewport(texture.second) {}
};

struct typeHeader {
    uint8_t HeaderVersion;            // Version of editor
    char    MapName[31]; // Filename

    struct Color {
        uint8_t BackgroundRed;   // RGB colour of background
        uint8_t BackgroundGreen; // RGB colour of background
        uint8_t BackgroundBlue;  // RGB colour of background
    } Color;

    struct Level {
        uint8_t  SizeX;    // Map width
        uint8_t  SizeY;    // Map height
        uint16_t Elements; // Number of active tiles
    } Level;
};

struct typeAssets {
    std::vector<std::string> Assets; //Asset names
};

struct typeLevelData {
    typeHeader     Header;
    typeAssets     Assets;
    typeTileData** Tiles;
};


/**
 * @brief Write the current struct to a file
 * @param filename Name of the file
 * @param data Data structure
 */
void
writeLevelDataToFile(const std::string& filename, const typeLevelData& data);

/**
 * @brief Load a file and return a map
 * @param filename
 * @return Pointer to the map
 */
typeLevelData*
readLevelData(const std::string& filename);
/**
 * @breif Returns a new Tile** based on the provided size
 * @param x Size in x
 * @param y Size in y
 * @return
 */
typeTileData**
newTileData(const int& x, const int& y);

/**
 * @brief Delete the tiles and free memory
 * @param tile Reference to tile object
 */
void
deleteTile(typeTileData** tile, const int& elements);
void
deleteTile(typeTile** tile, const int& elements);

void
removeAsset(const uint8_t& id, typeAssets* map);    //Delete an element from the list of assets

size_t
addAsset(const std::string& asset, typeAssets& map);   //Add a new item to the list, returns the id that was assigned

std::optional<size_t>
findAsset(const std::string& asset, const typeAssets& map);  //Search for an asset, -1 if item don't exist

}