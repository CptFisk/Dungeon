#include <algorithm>
#include <common/math.hpp>
#include <common/sdl.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <level/level.hpp>
#include <utility/textures.hpp>

namespace Level {

Level::Level(SDL_Renderer* renderer, std::shared_ptr<Graphics::Graphics> graphics, Uint8& red, Uint8& green, Uint8& blue, float& playerX, float& playerY)
  : pRenderer(renderer)
  , red(red)
  , green(green)
  , blue(blue)
  , playerX(playerX)
  , playerY(playerY)
  , header{}
  , mGraphics(std::move(graphics))
  , elements(0) {}



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

    tiles.clear(); // Clear if something exist

    for (int y = 0; y < data.Header.Level.SizeY; y++) {
        for (int x = 0; x < data.Header.Level.SizeX; x++) {
            tiles.emplace_back(x, y); // Used to generate all squares
        }
    }

    if (tiles.size() != data.Tiles.Tiles.size())
        throw std::runtime_error("Load file corrupted");

    int pos = 0; // Resetting
    for (const auto& tile : data.Tiles.Tiles) {
        if ((tile.Type & File::TEXTURE) != 0) {
            // Read all assets
            for (const auto& id : tile.Id) {
                const auto val     = static_cast<int>(id);
                auto       texture = GET_SIMPLE(data.Assets.Assets[val]); // Assets to use
                tiles[pos].addData(texture.getTexture(), texture.getRandomView(), texture.Width, texture.Height);
            }
        }
        if ((tile.Type & File::OBSTACLE) != 0) {
            const auto coords = Common::getCoords(pos, data.Header.Level.SizeX, data.Header.Level.SizeY);
            if (coords.has_value())
                obstacle.emplace_back(Common::newSDL_FRect(coords.value()));
        }
        pos++;
    }

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
    std::vector<Common::typeDrawData> data;
    std::vector<int> indices; // Contains all the tiles

    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            auto index = Common::getIndex(x, y, header.Level.SizeX);
            int  pos;
            if (index.has_value()) {
                pos = index.value();
                for (auto& element : tiles[pos].getTile())
                    data.push_back(element);
            }
        }
    }
    return data;
}

}