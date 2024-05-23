#pragma once
#include <SDL.h>
#include <cstdint>
#include <level/types/spawn.hpp>
#include <level/types/tile.hpp>
#include <optional>
#include <string>
#include <vector>

namespace Level::File {

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
        uint8_t  PlayerX;
        uint8_t  PlayerY;
    } Level;
};

struct typeAssets {
    std::vector<std::string> Assets; // Asset names
};

struct typeLevelData {
    typeHeader Header;
    typeAssets Assets;
    typeTiles  Tiles;
    typeSpawn  Spawns;
    typeLevelData(typeHeader header, typeAssets assets, typeTiles tiles, typeSpawn spawns)
      : Header(header)
      , Assets(std::move(assets))
      , Tiles(std::move(tiles))
      , Spawns(std::move(spawns)){};
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

/**
 * @brief Function used to remove a asset both from the game-world but also from the visual map that you are editing.
 * @param assetName Name of the asset
 * @param map Asset list
 * @param fileTiles Reference to the fileData structure
 * @return True if a element was found and removed
 */
bool
removeAsset(const std::string& assetName, typeAssets& map, Level::File::typeTiles& fileTiles);

}