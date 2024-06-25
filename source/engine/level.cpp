#include <algorithm>
#include <common/math.hpp>
#include <common/sdl.hpp>
#include <engine/engine.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <utility/math.hpp>
#include <utility/textures.hpp>
#include <global.hpp>

namespace Engine {

void
Engine::loadLevel(const std::string& filename) {
    //If a map is loaded, unload it.
    if(mLevelLoaded)
        clearLoadedLevel();

    auto data = Level::File::readLevelData("levels/" + filename);
    mHeader   = data.Header; // Catch header
    mFilename = filename;

    std::vector<SDL_FRect> obstacle;
    std::vector<SDL_FRect> wall;

    // Set background colors
    Background.Red   = mHeader.Color.BackgroundRed;
    Background.Green = mHeader.Color.BackgroundGreen;
    Background.Blue  = mHeader.Color.BackgroundBlue;

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

    for (const auto& door : data.Doors) {
        doors.emplace_back(new Objects::Door(door.X, door.Y, *GET_ANIMATED(door.GraphicOpen), *GET_ANIMATED(door.GraphicClosing)));
    }

    for(const auto& warp : data.Warps){
        warps.emplace_back(Objects::Warp(warp));
    }

    SDL_SetRenderTarget(pRenderer, nullptr);
    mMaxLayers = mSegments[0].Layers.size();
    mLevelLoaded = true;
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

    auto playerX = INT(pos.x / 16.0f);
    auto playerY = INT(pos.y / 16.0f);

    const auto index     = Common::getIndex(playerX, playerY, mHeader.Level.SizeX);

    if(((UINT8(levelObjects[index.value()]) & UINT8(Level::File::TileType::WALL)) != 0 ) ||
        ((UINT8(levelObjects[index.value()]) & UINT8(Level::File::TileType::OBSTACLE)) != 0 )
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
    return { mHeader.Level.PlayerX, mHeader.Level.PlayerY };
}

void
Engine::clearLoadedLevel() {
    //Reset all values
    mLevelLoaded = false;
    mHeader = {};
    mFilename = {};
    mCurrentLayer = {};
    mMaxLayers = {};

    //Clear segments
    for (auto& segment : mSegments) {
        for (auto& layer : segment.Layers) {
            SDL_DestroyTexture(layer);
        }
    }
    mSegments.clear();

    //Clear doors
    for (auto& door : doors) {
        delete door;
    }
    doors.clear();
    //Clear warps zones, they are not manually allocated so just clear the vector
    warps.clear();

}
}