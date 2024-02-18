#pragma once
#include <cstdint>
namespace Level {

enum TileType : uint8_t { Background, Obstacle };

struct Tile {
    TileType Type;
    size_t   Graphic;
};

struct LevelHeader {
    uint8_t HeaderVersion;
    char    MapName[31];

    uint8_t BackgroundRed;
    uint8_t BackgroundGreen;
    uint8_t BackgroundBlue;

    uint8_t MapSizeX;
    uint8_t MapSizeY;
};

struct LevelData{
    uint8_t Id;
    char Asset[31];
};

struct Level {
    LevelHeader Header;
    TileType*   Tiles;
};




}