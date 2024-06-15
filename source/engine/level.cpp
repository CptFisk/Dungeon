#include <algorithm>
#include <common/math.hpp>
#include <common/sdl.hpp>
#include <engine/engine.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <utility/math.hpp>
#include <utility/textures.hpp>

namespace Engine {

void
Engine::loadLevel(const std::string& filename) {
    auto data = Level::File::readLevelData(filename);
    header    = data.Header; // Catch header
    elements  = data.Header.Level.Elements;

    std::vector<SDL_FRect> obstacle;
    std::vector<SDL_FRect> wall;

    const auto sizeX = static_cast<float>(data.Header.Level.SizeX) * 16.0f;
    const auto sizeY = static_cast<float>(data.Header.Level.SizeY) * 16.0f;

    // Set background colors
    Background.Red   = header.Color.BackgroundRed;
    Background.Green = header.Color.BackgroundGreen;
    Background.Blue  = header.Color.BackgroundBlue;

    // Generate walls
    obstacle.push_back(SDL_FRect{ -16.0f, -16.0f, 16.0f, sizeY + 32.0f }); // Left wall
    obstacle.push_back(SDL_FRect{ sizeX, -16.0f, 16.0f, sizeY + 32.0f });  // Right wall
    obstacle.push_back(SDL_FRect{ -16.0f, -16.0f, sizeX, 16.0f });         // Top wall
    obstacle.push_back(SDL_FRect{ -16.0f, sizeY, sizeX, 16.0 });           // Bottom wall

    createSegments(data.Assets); // Generate segments

    const int tilesSize = data.Tiles.Tiles.size() - 1;
    int       pos       = 0;

    bool layersLeft = false;
    auto it         = data.Tiles.Tiles.begin();
    /**
     * This code will start with the first "layer" and go over all the tiles, if the tile have more sprite we
     * will set the flag layersLeft to true. This means that the next time we reach the end of the vector
     * we go back to the start, reset the flag and repeat the process over to see if this was the last layer.
     * If no more layers is found when we have reached the end we continue. This is to make sure that all drawings
     * appears in the correct order.
     */
    do {
        if (it == data.Tiles.Tiles.end()) {
            it = data.Tiles.Tiles.begin();
            pos = 0;
            layersLeft = false;
        }

        if (((it->Type & static_cast<uint8_t>(Level::File::TileType::TEXTURE)) != 0 ||
             ((it->Type & static_cast<uint8_t>(Level::File::TileType::ANIMATED_TEXTURE)) != 0)) &&
            !it->Id.empty()) {
            auto       id    = it->Id.front();
            const auto asset = data.Assets.Assets[static_cast<int>(id)];
            addToSegment(pos, asset);

            it->Id.erase(it->Id.begin()); // Remove this element, it has been displayed

            if (!it->Id.empty()) {
                layersLeft = true; // There is more
            }
        }

        // Add obstacles
        if ((it->Type & static_cast<uint8_t>(Level::File::TileType::OBSTACLE)) != 0) {
            const auto coords = Common::getCoords(pos, data.Header.Level.SizeX, data.Header.Level.SizeY);
            if (coords.has_value())
                obstacle.emplace_back(Common::newSDL_FRect(coords.value()));

            it->Type &= static_cast<uint8_t>(Level::File::TileType::OBSTACLE); // Reset bit
        }
        // Add walls
        if ((it->Type & static_cast<uint8_t>(Level::File::TileType::WALL)) != 0) {
            const auto coords = Common::getCoords(pos, data.Header.Level.SizeX, data.Header.Level.SizeY);
            if (coords.has_value())
                wall.emplace_back(Common::newSDL_FRect(coords.value()));
            it->Type &= static_cast<uint8_t>(Level::File::TileType::WALL); // Reset bit
        }
        pos++;

    } while (!(++it == data.Tiles.Tiles.end() && !layersLeft));
    clearDoors();

    for (const auto& door : data.Doors.Doors) {
        const auto position = Common::newSDL_FRect(door.X, door.Y);
        doors.emplace_back(new Objects::Door(position, GET_ANIMATED(door.GraphicOpen), GET_ANIMATED(door.GraphicClosing)));
    }

    SDL_SetRenderTarget(pRenderer, nullptr);
    walls     = wall;
    obstacles = obstacle;
    maxLayers = mSegments[0].Layers.size();
}

bool
Engine::movement(const SDL_FPoint& other, const Directions& direction) {
    return movement(SDL_FRect(other.x, other.y, 1.0f, 1.0f), direction);
}

bool
Engine::movement(const SDL_FRect& other, const Directions& direction) {
    for (const auto& wall : walls) {
        if (Utility::isColliding(other, wall, direction))
            return false;
    }
    for (const auto& obstacle : obstacles) {
        if (Utility::isColliding(other, obstacle, direction))
            return false;
    }
    for (const auto& door : doors) {
        if (!door->isPassable()) {
            if (Utility::isColliding(other, door->getPosition(), direction))
                return false;
        }
    }
    return true;
}

std::pair<uint8_t, uint8_t>
Engine::getPlayerSpawn() {
    return { header.Level.PlayerX, header.Level.PlayerY };
}

void
Engine::clearDoors() {
    for (auto& door : doors) {
        delete door;
    }
    doors.clear();
}
/*
std::vector<Common::typeDrawData>
Engine::getLevel() {
    std::vector<Common::typeDrawData> data;
    // Fetch the segments
    for (auto& segment : mSegments) {
        data.emplace_back(segment.second, nullptr, &segment.first);
    }
    // Add the doors over segments
    for (auto& door : doors) {
        data.emplace_back(door->getDrawData());
    }
    return data;
}
*/

void
Engine::interact(const SDL_FRect& area) {
    for (auto& door : doors) {
        if (Utility::isOverlapping(area, door->getPosition())) {
            door->interact(true);
            break;
        }
    }
}

}