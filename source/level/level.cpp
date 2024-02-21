#include <level/level.hpp>

namespace Level {

Level::Level(SDL_Renderer* renderer)
  : pRenderer(renderer)
  , mHeader{}
  , pTiles(nullptr) {}

Level::~Level() {
    const int size = mHeader.Level.SizeX * mHeader.Level.SizeY;
    if (pTiles != nullptr)
        deleteTile(pTiles, size);
}

bool
Level::loadLevel(const std::string& filename) {
    auto data          = readLevelData(filename);
    mHeader            = data->Header; // Catch header

    int       elements = 0; //Number of elements that have a tile
    for(unsigned short Type : data->Header.Level.Types)
        elements += Type;

    pTiles = new typeTile* [elements] {}; // Allocating
    int item = 0;
    for(int y = 0; y < data->Header.Level.SizeY; y++){
        for(int x = 0; x < data->Header.Level.SizeX; x++){
            //std::cout << data->Tiles[]
        }
    }

    delete data;

    // Do something fun here
}
}