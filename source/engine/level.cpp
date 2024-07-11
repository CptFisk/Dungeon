#include <algorithm>
#include <common/math.hpp>
#include <engine/engine.hpp>
#include <global.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <utility/math.hpp>
#include <utility/textures.hpp>

namespace Engine {

void
Engine::loadLevel(const std::string& filename) {
    // If a map is loaded, unload it.
    if (mLevelLoaded)
        clearLoadedLevel();

    auto data = Level::File::readLevelData("levels/" + filename);
    mHeader   = data.Header; // Catch header
    mFilename = filename;

    std::vector<SDL_FRect> obstacle;
    std::vector<SDL_FRect> wall;

    // Set background colors
    Background.Red   = mHeader.Colour.BackgroundRed;
    Background.Green = mHeader.Colour.BackgroundGreen;
    Background.Blue  = mHeader.Colour.BackgroundBlue;

    // Create segments
    createSegments(mSegments.Bottom, data.Assets.AnimationValueBase, mSegments.MaxLayerBottom);
    createSegments(mSegments.Top, data.Assets.AnimationValueTop, mSegments.MaxLayerTop);

    int pos = 0;

    levelObjects = std::vector<Level::File::TileType>(MAX_TILES, Level::File::TileType::BLANK);

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

        if (((it->Type & UINT8(Level::File::TileType::BASE_TEXTURE)) != 0 ||
             ((it->Type & UINT8(Level::File::TileType::TOP_TEXTURE)) != 0)) &&
            !it->Base.empty()) {
            const auto id    = INT(it->Base.front());
            const auto asset = data.Assets.Assets[id];
            addToSegment(mSegments.Bottom, pos, asset);

            it->Base.erase(it->Base.begin()); // Remove this element, it has been displayed

            if (!it->Base.empty())
                layersLeft = true; // There is more
        }
        // Overlay
        if (((it->Type & UINT8(Level::File::TileType::TOP_TEXTURE)) != 0) && !it->Top.empty()) {
            const auto id    = INT(it->Top.front());
            const auto asset = data.Assets.Assets[id];
            addToSegment(mSegments.Top, pos, asset);
            it->Top.erase(it->Top.begin()); // Remove element
            if (!it->Top.empty())
                layersLeft = true;
        }

        // Add obstacles
        if ((it->Type & UINT8(Level::File::TileType::OBSTACLE)) != 0) {
            levelObjects[pos] = static_cast<Level::File::TileType>(UINT8(Level::File::TileType::OBSTACLE) | UINT8(levelObjects[pos]));
            it->Type &= ~UINT8(Level::File::TileType::OBSTACLE); // Reset bit
        }
        // Add walls
        if ((it->Type & UINT8(Level::File::TileType::WALL)) != 0) {
            levelObjects[pos] = static_cast<Level::File::TileType>(UINT8(Level::File::TileType::WALL) | UINT8(levelObjects[pos]));
            it->Type &= ~UINT8(Level::File::TileType::WALL); // Reset bit
        }
        // Add transportation up
        if ((it->Type & UINT8(Level::File::TileType::UP)) != 0) {

            it->Type &= ~UINT8(Level::File::TileType::UP); // Reset bit
        }
        // Add transportation down
        if ((it->Type & UINT8(Level::File::TileType::DOWN)) != 0) {
            const auto coords = Common::getCoords(pos, MAP_SIZE, MAP_SIZE);
            if (coords.has_value() && mHeader.MapCoordinate.Z > 0) {
                const auto origin  = mHeader.MapCoordinate;
                const auto& [x, y] = coords.value();
                // Reduce our Z-layer by one
                Level::File::type3DMapCoordinate level(origin.X, origin.Y, origin.Z - 1);
                Level::File::type2DMapCoordinate destination(x, y);
                warp[pos] = new Objects::Warp(level, destination);
            } else {
                std::cerr << "Not a valid coordinate" << std::endl;
            }
            it->Type &= ~UINT8(Level::File::TileType::DOWN); // Reset bit
        }
        pos++;

    } while (!(++it == data.Tiles.Tiles.end() && !layersLeft));

    for (const auto& door : data.Doors) {
        doors.emplace_back(new Objects::Door(door.X, door.Y, *GET_ANIMATED(door.GraphicOpen), *GET_ANIMATED(door.GraphicClosing)));
    }

    SDL_SetRenderTarget(pRenderer, nullptr);
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
    if (pos.x < 0 || pos.y < 0)
        return false; // No need to evaluate more
    auto playerX = INT(pos.x / 16.0f);
    auto playerY = INT(pos.y / 16.0f);

    const auto index = Common::getIndex(playerX, playerY, MAP_SIZE);
    if (!index.has_value())
        return false;
    if (((UINT8(levelObjects[index.value()]) & UINT8(Level::File::TileType::WALL)) != 0) ||
        ((UINT8(levelObjects[index.value()]) & UINT8(Level::File::TileType::OBSTACLE)) != 0)) {
        return false;
    }
    auto it = warp.find(index.value());
    if (it != warp.end()) {
        const auto object = (*it).second;
        const auto level  = object->getLevel();
        if (level != mHeader.MapCoordinate) {
            loadLevel(object->getLevel().toString() + ".map");
            mPlayer->spawn(object->getDestination());
            mPerspective->center(pPlayerPosition->x + 8.0f, pPlayerPosition->y + 8.0f);
        }else{
            std::cout << "Swap level" << std::endl;
        }
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

void
Engine::clearLoadedLevel() {
    // Reset all values
    mLevelLoaded = false;
    mHeader      = {};
    mFilename    = {};

    // Clear segments
    clearTypeSegment(mSegments);

    // Clear doors
    for (auto& door : doors) {
        delete door;
    }
    doors.clear();
    // Clear warps zones, they are not manually allocated so just clear the vector
    for (auto& [position, object] : warp)
        delete object;
    warp.clear();
}
}