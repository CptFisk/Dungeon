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

struct Level {
    LevelHeader Header;
    TileType*   Tiles;
};

Level* getNewLevel(const uint8_t maxX, const uint8_t maxY){
    Level* level = new Level;
    level->Header.MapSizeX = maxX;
    level->Header.MapSizeY = maxY;
    size_t tiles = static_cast<size_t>(maxX) * static_cast<size_t>(maxY);
    level->Tiles = new TileType[tiles];

    return level;
}



}