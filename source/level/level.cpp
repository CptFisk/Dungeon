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

    mElements = 0; // Number of elements that have a tile
    for (unsigned short Type : data->Header.Level.Types)
        mElements  += Type;
    pTiles = new typeTile* [mElements] {}; // Allocating

    int item = 0; // Keep track of current position
    for (int y = 0; y < data->Header.Level.SizeY; y++) {
        for (int x = 0; x < data->Header.Level.SizeX; x++) {
            switch (data->Tiles[Common::getIndex(x, y, &data->Header)]->Type) {
                case TEXTURE:
                    pTiles[item++] = new typeTile(
                      TEXTURE, Common::newSDL_FRect(x, y, mScale), mGraphics->getBaseTexture("PurpleFloor")[-1]);
                    break;
                case OBSTACLE:
                    break;
                case BLANK:
                default:
                    break;
            }
        }
    }

    printf("%i\n", item);
    delete data;

}

void Level::draw() {
    if(pTiles != nullptr){
        for(int i = 0; i < mElements ; i++){
            SDL_RenderTexture(pRenderer,pTiles[i]->Texture, &pTiles[i]->Viewport, &pTiles[i]->Position);
        }
    }
}
}