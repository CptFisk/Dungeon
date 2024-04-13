#pragma once
#include <SDL3/SDL.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace Level::File {
/**
 * All this types is only used for generating and loading a pre-defined map file.
 */
enum TileType : uint8_t { BLANK = 0, TEXTURE = 1 << 0, WALL = 1 << 1, OBSTACLE = 1 << 2 };

/**
 * @brief Definition of a single tile. A can have multiple properties and they are each stored as a single bit in Type.
 * @brief The element Id contains a list of all Assets that is used. Since a tile can have multiple assets linked to it.
 */
struct typeTileData {
    uint8_t              Type; // Tiletype
    std::vector<uint8_t> Id;   // Reference to assets. Drawn from bottom to top
    typeTileData()
      : Type(0){};
};

/**
 * @brief Structure used to store all the tiles and assets that each tile uses. This structure is only used when writing/loading a map file
 * @var Size Contains the size of x*y
 * @var Tiles Contains all the tiles.
 */
struct typeTiles {
    uint16_t                  Size; // Number of tiles defined
    std::vector<typeTileData> Tiles;

    // Constructor
    explicit typeTiles(uint16_t size)
      : Size(size) {
        Tiles.resize(size);
    }
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
    uint8_t HeaderVersion; // Version of editor
    char    MapName[31];   // Filename

    struct Color {
        uint8_t BackgroundRed;   // RGB colour of background
        uint8_t BackgroundGreen; // RGB colour of background
        uint8_t BackgroundBlue;  // RGB colour of background
        Color()
          : BackgroundRed(0)
          , BackgroundGreen(0)
          , BackgroundBlue(0){};
    } Color;

    struct Level {
        uint8_t  SizeX;    // Map width
        uint8_t  SizeY;    // Map height
        uint16_t Elements; // Number of active tiles
    } Level;
    /*
    typeHeader()
      : HeaderVersion(0)
      , MapName{}
      , Color()
      , Level(){};
      */
};

struct typeAssets {
    std::vector<std::string> Assets; // Asset names
};

struct typeLevelData {
    typeHeader Header;
    typeAssets Assets;
    typeTiles  Tiles;
    typeLevelData(typeHeader header, typeAssets assets, typeTiles tiles)
      : Header(header)
      , Assets(assets)
      , Tiles(tiles){};
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
typeLevelData
readLevelData(const std::string& filename);

size_t
addAsset(const std::string& asset, typeAssets& map); // Add a new item to the list, returns the id that was assigned

std::optional<size_t>
findAsset(const std::string& asset, const typeAssets& map); // Search for an asset, -1 if item don't exist

}