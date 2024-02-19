#pragma once
#include <cstdint>
namespace Level {

const int MAP_META_MAX = 31;

enum TileType : uint8_t { Background, Obstacle };

struct Tile {
    TileType Type; // Tiletype
    uint8_t  Id;   // Id used in SubMetaFiles
};

struct LevelHeader {
    uint8_t HeaderVersion; // Version of editor
    char    MapName[31];   // Filename

    uint8_t BackgroundRed;   // RGB colour of background
    uint8_t BackgroundGreen; // RGB colour of background
    uint8_t BackgroundBlue;  // RGB colour of background

    uint8_t MapSizeX; // Map width
    uint8_t MapSizeY; // Map height
};

struct SubFileMeta {
    uint8_t Id;        // Unique id of the file 1-32
    char    Asset[31]; // Asset name
};

struct MapMeta {
    SubFileMeta Data[MAP_META_MAX]; // A file can only contain 32 sub-files
};

struct Map {
    LevelHeader Header;
    MapMeta     Meta;
    Tile**   Tiles;
};


Tile** newTile(const int& x, const int& y);
void deleteMapMeta(const uint8_t& id, MapMeta* map);
bool addMapMeta(const char* asset, MapMeta* map);

}