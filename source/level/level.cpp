#include <level/level.hpp>

namespace Level {

Level::Level(SDL_Renderer* renderer)
  : pRenderer(renderer)
  , mHeader{}
  , pTiles(nullptr) {}

Level::~Level() {
    const int size = mHeader.SizeX * mHeader.SizeY;
    if (pTiles != nullptr)
        deleteTile(pTiles, size);
}

bool
Level::loadLevel(const std::string& filename) {
    auto data          = readLevelData(filename);
    mHeader            = data->Header; // Catch header
    const int size     = data->Header.SizeX * data->Header.SizeY;
    int       elements = 0; //Number of elements that have a tile

    // Calculating how many elements is actually a tile
    for (int i = 0; i < size; i++) {
        if (data->Tiles[i]->Type != BLANK)
            elements++;
    }
    pTiles = new typeTile* [size] {}; // Allocating

    delete data;

    // Do something fun here
}
}