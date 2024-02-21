#include <common/math.hpp>
#include <common/sdl.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <level/level.hpp>

namespace Level {

Level::Level(SDL_Renderer* renderer, const Common::typeScale& scale, std::shared_ptr<Graphics::Graphics> graphics)
  : pRenderer(renderer)
  , mScale(scale)
  , mHeader{}
  , mGraphics(std::move(graphics))
  , pTiles(nullptr) {}

Level::~Level() {
    const int size = mHeader.Level.SizeX * mHeader.Level.SizeY;
    if (pTiles != nullptr)
        deleteTile(pTiles, size);
}

void
Level::loadLevel(const std::string& filename) {
    auto data      = readLevelData(filename);
    mHeader        = data->Header; // Catch header
    const int size = data->Header.Level.SizeX * data->Header.Level.SizeY;

    int elements = 0; // Number of elements that have a tile
    for (unsigned short Type : data->Header.Level.Types)
        elements += Type;
    pTiles = new typeTile* [elements] {}; // Allocating

    int item = 0; // Keep track of current position
    for (int y = 0; y < data->Header.Level.SizeY; y++) {
        for (int x = 0; x < data->Header.Level.SizeX; x++) {
            switch (data->Tiles[Common::getIndex(x, y, &data->Header)]->Type) {
                case BACKGROUND:
                    pTiles[item++] = new typeTile{ BACKGROUND,
                                                   Common::newSDL_FRect(x, y, mScale),
                                                   mGraphics->getTexture("PurpleFloor") };
                    break;
                case OBSTACLE:
                    break;
                case BLANK:
                default:
                    break;
            }
        }
    }

    delete data;

    // Do something fun here
}
}