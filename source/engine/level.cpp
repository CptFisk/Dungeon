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

    // Set background colors
    Background.Red   = header.Color.BackgroundRed;
    Background.Green = header.Color.BackgroundGreen;
    Background.Blue  = header.Color.BackgroundBlue;

    createSegments(data.Assets); // Generate segments

    int pos = 0;

    const int mapSize = static_cast<float>(data.Header.Level.SizeX) * static_cast<float>(data.Header.Level.SizeY);
    levelObjects      = std::vector<Level::File::TileType>(mapSize, Level::File::TileType::BLANK);

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
            it         = data.Tiles.Tiles.begin();
            pos        = 0;
            layersLeft = false;
        }

        if (((it->Type & static_cast<uint8_t>(Level::File::TileType::TEXTURE)) != 0 ||
             ((it->Type & static_cast<uint8_t>(Level::File::TileType::ANIMATED_TEXTURE)) != 0)) &&
            !it->Id.empty()) {
            auto       id    = static_cast<int>(it->Id.front());
            const auto asset = data.Assets.Assets[id];
            if (asset == "VillageHouseBaseMedium") {
                int a = 20;
            }
            addToSegment(pos, asset);

            it->Id.erase(it->Id.begin()); // Remove this element, it has been displayed

            if (!it->Id.empty()) {
                layersLeft = true; // There is more
            }
        }

        // Add obstacles
        if ((it->Type & static_cast<uint8_t>(Level::File::TileType::OBSTACLE)) != 0) {
            levelObjects[pos] = static_cast<Level::File::TileType>(static_cast<uint8_t>(Level::File::TileType::OBSTACLE) |
                                                                   static_cast<uint8_t>(levelObjects[pos]));
            it->Type &= ~static_cast<uint8_t>(Level::File::TileType::OBSTACLE); // Reset bit
        }
        // Add walls
        if ((it->Type & static_cast<uint8_t>(Level::File::TileType::WALL)) != 0) {
            levelObjects[pos] = static_cast<Level::File::TileType>(static_cast<uint8_t>(Level::File::TileType::WALL) |
                                                                   static_cast<uint8_t>(levelObjects[pos]));
            it->Type &= ~static_cast<uint8_t>(Level::File::TileType::WALL); // Reset bit
        }
        pos++;

    } while (!(++it == data.Tiles.Tiles.end() && !layersLeft));
    clearDoors();

    for (const auto& door : data.Doors.Doors) {
        const auto position = Common::newSDL_FRect(door.X, door.Y);
        doors.emplace_back(new Objects::Door(position, GET_ANIMATED(door.GraphicOpen), GET_ANIMATED(door.GraphicClosing)));
    }

    SDL_SetRenderTarget(pRenderer, nullptr);
    maxLayers = mSegments[0].Layers.size();
}

bool
Engine::movement(const SDL_FPoint& other, const Directions& direction) {
    return movement(SDL_FRect(other.x, other.y, 1.0f, 1.0f), direction);
}

bool
Engine::movement(const SDL_FRect& other, const Directions& direction) {
    auto pos = other;
    const float threshold = 1.0f;
    switch (direction) {
        case NORTH:
            pos.y -= threshold;
            break;
        case EAST:
            pos.x += threshold;
            break;
        case SOUTH:
            pos.y += threshold;
            break;
        case WEST:
            pos.x -= threshold;
            break;
        case ALL:
        default:
            break;
    }

    auto playerX = static_cast<int>(pos.x / 16.0f);
    auto playerY = static_cast<int>(pos.y / 16.0f);

    const auto index     = Common::getIndex(playerX, playerY, header.Level.SizeX);

    if(((static_cast<uint8_t>(levelObjects[index.value()]) & static_cast<uint8_t>(Level::File::TileType::WALL)) != 0 ) ||
        ((static_cast<uint8_t>(levelObjects[index.value()]) & static_cast<uint8_t>(Level::File::TileType::OBSTACLE)) != 0 )
        ){
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

}