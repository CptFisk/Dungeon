#include <common/math.hpp>
#include <common/sdl.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <level/level.hpp>
#include <utility/textures.hpp>

namespace Level {

Level::Level(SDL_Renderer* renderer, std::shared_ptr<Graphics::Graphics> graphics, Uint8& red, Uint8& green, Uint8& blue)
  : pRenderer(renderer)
  , red(red)
  , green(green)
  , blue(blue)
  , header{}
  , mGraphics(std::move(graphics))
  , elements(0) {}

Level::~Level() {}

void
Level::loadLevel(const std::string& filename) {
    auto data = File::readLevelData(filename);
    header    = data.Header; // Catch header
    elements  = data.Header.Level.Elements;

    std::vector<SDL_FRect> obstacle;
    std::vector<SDL_FRect> wall;
    const auto             sizeX = static_cast<float>(data.Header.Level.SizeX) * 16.0f;
    const auto             sizeY = static_cast<float>(data.Header.Level.SizeY) * 16.0f;

    // Set background colors
    red   = header.Color.BackgroundRed;
    green = header.Color.BackgroundGreen;
    blue  = header.Color.BackgroundBlue;

    // Generate walls
    obstacle.push_back(SDL_FRect{ -16.0f, -16.0f, 16.0f, sizeY + 32.0f }); // Left wall
    obstacle.push_back(SDL_FRect{ sizeX, -16.0f, 16.0f, sizeY + 32.0f });  // Right wall
    obstacle.push_back(SDL_FRect{ -16.0f, -16.0f, sizeX, 16.0f });         // Top wall
    obstacle.push_back(SDL_FRect{ -16.0f, sizeY, sizeX, 16.0 });           // Bottom wall

    tiles.clear();          // Clear if something exist
    tiles.resize(data.Header.Level.SizeX * data.Header.Level.SizeY);
    int pos = 0;
    for(int y = 0; y < data.Header.Level.SizeY; y++){
        for(int x = 0; x < data.Header.Level.SizeX; x++) {
            tiles[pos] = Tile(x, y);    //Used to generate all squares
        }
    }


    for (int y = 0; y < data.Header.Level.SizeY; y++) {
        for (int x = 0; x < data.Header.Level.SizeX; x++) {
            if ((data.Tiles.Tiles[pos].Type & File::TEXTURE) != 0) {
                //for (const auto& id : data.Tiles.Tiles[pos].Id)
                ;
            }
        }
    }
    /*
    int item = 0; // Keep track of current position
    for (int y = 0; y < data->Header.Level.SizeY; y++) {
        for (int x = 0; x < data->Header.Level.SizeX; x++) {
            const auto index = Common::getIndex(x, y, &data->Header);
            // Shall texture be added
            if ((data->Tiles[index]->Type & TEXTURE) != 0) {
                pTiles[item++] = new typeTile(TEXTURE, Common::newSDL_FRect(x, y),
    GET_SIMPLE(data->Assets.Data[data->Tiles[index]->Id].Assets)[-1]);
            }
            if ((data->Tiles[index]->Type & WALL) != 0) {
                wall.push_back(Common::newSDL_FRect(x, y));
            }
            if ((data->Tiles[index]->Type & OBSTACLE) != 0) {
                obstacle.push_back(Common::newSDL_FRect(x, y));
            }
        }
    }
     */
    walls     = wall;
    obstacles = obstacle;
}

bool
Level::movement(const SDL_FRect& other, const Directions& direction) {
    for (const auto& wall : walls) {
        if (Utility::isColliding(other, wall, direction))
            return false;
    }
    for (const auto& obstacle : obstacles) {
        if (Utility::isColliding(other, obstacle, direction))
            return false;
    }
    return true;
}

std::vector<Common::typeDrawData>
Level::getLevel() {
    /*
    if (pTiles != nullptr) {
        std::vector<Common::typeDrawData> data;
        for (int i = 0; i < elements; i++)
            data.emplace_back(pTiles[i]->Texture, &pTiles[i]->Viewport, &pTiles[i]->Position);
        return data;
    }
    return std::vector<Common::typeDrawData>{};
     */
}

}