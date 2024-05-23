#include <algorithm>
#include <common/math.hpp>
#include <common/sdl.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <level/level.hpp>
#include <utility/math.hpp>
#include <utility/textures.hpp>

namespace Level {

Level::Level(SDL_Renderer*                       renderer,
             std::shared_ptr<Graphics::Graphics> graphics,
             Uint8&                              red,
             Uint8&                              green,
             Uint8&                              blue,
             float&                              playerX,
             float&                              playerY)
  : pRenderer(renderer)
  , red(red)
  , green(green)
  , blue(blue)
  , playerX(playerX)
  , playerY(playerY)
  , header{}
  , mGraphics(std::move(graphics))
  , elements(0) {}

Level::~Level(){
    for(auto &[position, texture] : mSegments){
        SDL_DestroyTexture(texture);
    }
}

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

    int pos = data.Tiles.Tiles.size() - 1; // Resetting, minus one to get correct values
    createSegments();                  // Generate segments

    //The reason for looping in reverse order is because of how items is drawn to the screen
    for (auto it = data.Tiles.Tiles.rbegin(); it != data.Tiles.Tiles.rend(); ++it) {
        if (((*it).Type & static_cast<uint8_t>(File::TileType::TEXTURE)) != 0) {
            for(const auto& id : (*it).Id){
                addToSegment(pos, data.Assets.Assets[static_cast<int>(id)]);
            }
        }
        if (((*it).Type & static_cast<uint8_t>(File::TileType::OBSTACLE)) != 0) {
            const auto coords = Common::getCoords(pos, data.Header.Level.SizeX, data.Header.Level.SizeY);
            if (coords.has_value())
                obstacle.emplace_back(Common::newSDL_FRect(coords.value()));
        }
        if (((*it).Type & static_cast<uint8_t>(File::TileType::WALL)) != 0) {
            const auto coords = Common::getCoords(pos, data.Header.Level.SizeX, data.Header.Level.SizeY);
            if (coords.has_value())
                wall.emplace_back(Common::newSDL_FRect(coords.value()));
        }
        pos--;
    }

    SDL_SetRenderTarget(pRenderer, nullptr);
    walls     = wall;
    obstacles = obstacle;
}

bool
Level::movement(const SDL_FPoint& other, const Directions& direction) {
    return movement(SDL_FRect(other.x, other.y, 1.0f, 1.0f), direction);
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

std::pair<uint8_t, uint8_t>
Level::getPlayerSpawn() {
    return { header.Level.PlayerX, header.Level.PlayerY };
}

std::vector<Common::typeDrawData>
Level::getLevel() {
    std::vector<Common::typeDrawData> data;
    //SDL_RenderTexture(pRenderer, mSegments[0].second, nullptr, &mSegments[0].first);
    /*

    std::vector<int>                  indices; // Contains all the tiles

    // Calculate what to draw
    const auto minX = std::max(static_cast<int>((playerX / -1.0f) / 16.0f - 3.0f), 0);
    const auto minY = std::max(static_cast<int>((playerY / -1.0f) / 16.0f - 3.0f), 0);
    const auto maxX = std::min(minX + 20, static_cast<int>(header.Level.SizeX));
    const auto maxY = std::min(minY + 16, static_cast<int>(header.Level.SizeY));

    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {
            auto pos = Common::getIndex(x, y, header.Level.SizeX);
            if (pos.has_value()) {
                indices.emplace_back(pos.value());
            }
        }
        size_t maxSize = 0;
        for (const auto& index : indices) {
            maxSize = std::max(maxSize, tiles[index].getDrawData().size()); // Selecting the biggest value
        }

        for (int i = 0; i < maxSize; i++) {
            for (const auto& index : indices) {
                if (index < tiles.size() && i < tiles[index].getDrawData().size()) {
                    auto element = tiles[index].getDrawData()[i];
                    data.emplace_back(element.Texture, element.Viewport, element.Position);
                }
            }
        }
    }
     */
    return data;
}

}