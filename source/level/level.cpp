#include <level/level.hpp>

namespace Level {

Level::Level(SDL_Renderer* renderer)
  : pRenderer(renderer)
  , mHeader{}
  , pTiles(nullptr) {}

Level::~Level() {
    const int size = mHeader.MapSizeX * mHeader.MapSizeY;
    if(pTiles != nullptr)
        deleteTile(pTiles, size);
}

bool
Level::loadLevel(const std::string& filename) {
    auto data = readLevelData(filename);
    mHeader = data->Header;
    delete data;

    //Do something fun here
}
}