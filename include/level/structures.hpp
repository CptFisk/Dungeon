#pragma once
#include <cstdint>
#include <string>

namespace Level {

const int MAP_META_MAX      = 31;
const int LEVEL_HEADER_MAX  = 31;
const int SUB_FILE_META_MAX = 31;

enum TileType : uint8_t { Black = 0, Background = 1 << 1, Obstacle = 1 << 2 };

struct typeTile {
    TileType Type; // Tiletype
    uint8_t  Id;   // ID used in SubMetaFiles
};

struct typeHeader {
    uint8_t HeaderVersion;             // Version of editor
    char    MapName[LEVEL_HEADER_MAX]; // Filename

    uint8_t BackgroundRed;   // RGB colour of background
    uint8_t BackgroundGreen; // RGB colour of background
    uint8_t BackgroundBlue;  // RGB colour of background

    uint8_t MapSizeX; // Map width
    uint8_t MapSizeY; // Map height
};

struct typeAssetItem {
    uint8_t Id;                       // Unique id of the file 1-32
    char    Asset[SUB_FILE_META_MAX]; // Asset name
};

struct typeAssets {
    typeAssetItem Data[MAP_META_MAX]; // A file can only contain 32 sub-files
};

struct typeLevelData {
    typeHeader Header;
    typeAssets Assets;
    typeTile** Tiles;
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
typeTile**
newTile(const int& x, const int& y);

/**
 * @brief Delete the tiles and free memory
 * @param tile Reference to tile object
 */
void
deleteTile(typeTile** tile, const int& elements);

/**
 * @brief Delete a element from the list of assets
 * @param id
 * @param map
 */
void
removeAsset(const uint8_t& id, typeAssets* map);

/**
 * @brief Add a new element to the list of assets
 * @param asset Name of the asset
 * @param map Reference to the map
 * @return True if it was added
 */
bool
addAsset(const char* asset, typeAssets* map);

}