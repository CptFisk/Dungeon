#include <common/math.hpp>
#include <common/sdl.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <level/level.hpp>
#include <utility/textures.hpp>

namespace Level {

Level::Level(SDL_Renderer* renderer, const Common::typeScale& scale, std::shared_ptr<Graphics::Graphics> graphics)
  : pRenderer(renderer)
  , mScale(scale)
  , mHeader{}
  , mGraphics(std::move(graphics))
  , pTiles(nullptr)
  , mElements(0) {}

Level::~Level() {
    if (pTiles != nullptr)
        deleteTile(pTiles, mElements);
}

void
Level::loadLevel(const std::string& filename) {
    auto data = readLevelData(filename);
    mHeader   = data->Header; // Catch header

    mElements = data->Header.Level.Elements;
    pTiles    = new typeTile* [mElements] {}; // Allocating
    std::vector<SDL_FRect> obstacle;
    std::vector<SDL_FRect> wall;
    const auto             sizeX = static_cast<float>(data->Header.Level.SizeX) * 16.0f;
    const auto             sizeY = static_cast<float>(data->Header.Level.SizeY) * 16.0f;
    // Generate walls
    obstacle.push_back(SDL_FRect{ -16.0f, -16.0f, 16.0f, (sizeY * mScale.ScaleY) + 32.0f });                // Left wall
    obstacle.push_back(SDL_FRect{ sizeX * mScale.ScaleX, -16.0f, 16.0f, (sizeY * mScale.ScaleY) + 32.0f }); // Right wall
    obstacle.push_back(SDL_FRect{ -16.0f, -16.0f, sizeX * mScale.ScaleX, 16.0f });                          // Top wall
    obstacle.push_back(SDL_FRect{ -16.0f, (sizeY * mScale.ScaleY), sizeX * mScale.ScaleX, 16.0 });          // Bottom wall

    int item = 0; // Keep track of current position
    for (int y = 0; y < data->Header.Level.SizeY; y++) {
        for (int x = 0; x < data->Header.Level.SizeX; x++) {
            // Shall texture be added
            if ((data->Tiles[Common::getIndex(x, y, &data->Header)]->Type & TEXTURE) != 0) {

                pTiles[item++] = new typeTile(
                  TEXTURE, Common::newSDL_FRect(x, y, mScale), mGraphics->getTexture<Graphics::typeSimpleTexture>("PurpleFloor")[-1]);
            }
            if ((data->Tiles[Common::getIndex(x, y, &data->Header)]->Type & WALL) != 0) {
                wall.push_back(Common::newSDL_FRect(x, y, mScale));
            }
            if ((data->Tiles[Common::getIndex(x, y, &data->Header)]->Type & OBSTACLE) != 0) {
                obstacle.push_back(Common::newSDL_FRect(x, y, mScale));
            }
        }
    }
    mWalls    = wall;
    mObstacle = obstacle;
    delete data;
}

bool
Level::movement(const SDL_FRect& other, const Directions& direction) {
    for (const auto& wall : mWalls) {
        if (Utility::isColliding(other, wall, direction))
            return false;
    }
    for (const auto& obstacle : mObstacle) {
        if (Utility::isColliding(other, obstacle, direction))
            return false;
    }
    return true;
}

void
Level::draw() {
    SDL_SetRenderDrawColor(
      pRenderer, mHeader.Color.BackgroundRed, mHeader.Color.BackgroundGreen, mHeader.Color.BackgroundBlue, SDL_ALPHA_OPAQUE);
    if (pTiles != nullptr) {
        for (int i = 0; i < mElements; i++) {
            SDL_RenderTexture(pRenderer, pTiles[i]->Texture, &pTiles[i]->Viewport, &pTiles[i]->Position);
        }
    }
}
}