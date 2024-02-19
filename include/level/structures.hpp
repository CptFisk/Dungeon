#pragma once
#include <cstdint>
#include <string>

namespace Level {

const int MAP_META_MAX      = 31;
const int LEVEL_HEADER_MAX  = 31;
const int SUB_FILE_META_MAX = 31;

enum TileType : uint8_t { Background = 1 << 1, Obstacle = 1 << 2 };

struct Tile {
    TileType Type; // Tiletype
    uint8_t  Id;   // ID used in SubMetaFiles
};

struct Header {
    uint8_t HeaderVersion;             // Version of editor
    char    MapName[LEVEL_HEADER_MAX]; // Filename

    uint8_t BackgroundRed;   // RGB colour of background
    uint8_t BackgroundGreen; // RGB colour of background
    uint8_t BackgroundBlue;  // RGB colour of background

    uint8_t MapSizeX; // Map width
    uint8_t MapSizeY; // Map height
};

struct Asset {
    uint8_t Id;                       // Unique id of the file 1-32
    char    Asset[SUB_FILE_META_MAX]; // Asset name
};

struct Assets {
    Asset Data[MAP_META_MAX]; // A file can only contain 32 sub-files
};

struct Map {
    Header Header;
    Assets Meta;
    Tile** Tiles;
};

void
writeMapToFile(const std::string& filename, const Map& data);
Tile**
newTile(const int& x, const int& y);
void
deleteMapMeta(const uint8_t& id, Assets* map);
bool
addMapMeta(const char* asset, Assets* map);

}