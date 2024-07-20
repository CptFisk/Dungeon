#include <algorithm>
#include <common/math.hpp>
#include <engine/engine.hpp>
#include <engine/helper/functions.hpp>
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

    levelObjects = std::vector<Level::File::TileType>(MAP_SIZE);

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

        if (((it->Type.test(Level::File::TileType::BASE_TEXTURE) ||
             it->Type.test(Level::File::TileType::TOP_TEXTURE)) && !it->Base.empty())) {
            const auto id    = INT(it->Base.front());
            const auto asset = data.Assets.Assets[id];
            addToSegment(mSegments.Bottom, pos, asset);

            it->Base.erase(it->Base.begin()); // Remove this element, it has been displayed

            if (!it->Base.empty())
                layersLeft = true; // There is more
        }
        // Overlay
        if (it->Type.test(Level::File::TileType::TOP_TEXTURE) && !it->Top.empty()) {
            const auto id    = INT(it->Top.front());
            const auto asset = data.Assets.Assets[id];
            addToSegment(mSegments.Top, pos, asset);
            it->Top.erase(it->Top.begin()); // Remove element
            if (!it->Top.empty())
                layersLeft = true;
        }

        // Add obstacles
        if (it->Type.test(Level::File::TileType::OBSTACLE)) {
            levelObjects[pos] = static_cast<Level::File::TileType>(UINT8(Level::File::TileType::OBSTACLE) | UINT8(levelObjects[pos]));
            it->Type.reset(Level::File::TileType::OBSTACLE);
        }
        // Add walls
        if (it->Type.test(Level::File::TileType::WALL)) {
            levelObjects[pos] = static_cast<Level::File::TileType>(UINT8(Level::File::TileType::WALL) | UINT8(levelObjects[pos]));
            it->Type.reset(Level::File::TileType::WALL); // Reset bit
        }
        // Add transportation up
        if (it->Type.test(Level::File::TileType::UP)) {
            const auto coords = Common::getCoords(pos, MAP_WIDTH, MAP_WIDTH);
            if (coords.has_value() && mHeader.MapCoordinate.Z > 0) {
                const auto origin  = mHeader.MapCoordinate;
                const auto& [x, y] = coords.value();
                // Reduce our Z-layer by one
                Level::File::type3DMapCoordinate level(origin.X, origin.Y, origin.Z + 1);
                Level::File::type2DMapCoordinate destination(x, y + 1);
                warp[pos] = new Objects::Warp(level, destination);
            } else {
                std::cerr << "Not a valid coordinate" << std::endl;
            }
            it->Type.reset(Level::File::TileType::UP);
        }
        // Add transportation down
        if (it->Type.test(Level::File::TileType::DOWN)) {
            const auto coords = Common::getCoords(pos, MAP_WIDTH, MAP_WIDTH);
            if (coords.has_value() && mHeader.MapCoordinate.Z > 0) {
                const auto origin  = mHeader.MapCoordinate;
                const auto& [x, y] = coords.value();
                // Reduce our Z-layer by one
                Level::File::type3DMapCoordinate level(origin.X, origin.Y, origin.Z - 1);
                Level::File::type2DMapCoordinate destination(x, y + 1);
                warp[pos] = new Objects::Warp(level, destination);
            } else {
                std::cerr << "Not a valid coordinate" << std::endl;
            }
            it->Type.reset(Level::File::TileType::DOWN); // Reset bit
        }
        pos++;

    } while (!(++it == data.Tiles.Tiles.end() && !layersLeft));

    for (const auto& door : data.Doors) {
        doors.emplace_back(new Objects::Door(door.X, door.Y, *GET_ANIMATED(door.GraphicOpen), *GET_ANIMATED(door.GraphicClosing)));
    }

    SDL_SetRenderTarget(pRenderer, nullptr);
    mLevelLoaded = true;
    // Run all startup functions
    for (const auto& name : data.Header.OnLoad) {
        auto function = getExternalFunction(name);
        if (function)
            function();
        else
            std::cerr << "Function: " << name << " could not be found" << std::endl;
    }
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

    const auto index = Common::getIndex(playerX, playerY, MAP_WIDTH);
    if (!index.has_value())
        return false;
    if (((UINT8(levelObjects[index.value()]) & UINT8(Level::File::TileType::WALL)) != 0) ||
        ((UINT8(levelObjects[index.value()]) & UINT8(Level::File::TileType::OBSTACLE)) != 0)) {
        return false;
    }
    auto it = warp.find(index.value());
    if (it != warp.end()) {
        auto       object = it->second;
        const auto level  = object->getLevel();
        if (level != mHeader.MapCoordinate) {
            const auto destination = object->getDestination(); // Need to store before swapping map
            loadLevel(object->getLevel().toString() + ".map");
            mPlayer->spawn(destination);
            mPerspective->center(pPlayerPosition->x + 8.0f, pPlayerPosition->y + 8.0f);
        } else {
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
    // Run functions on unLoad
    for (const auto& name : mHeader.OnExit) {
        auto function = getExternalFunction(name);
        if (function)
            function();
        else
            std::cerr << "Function: " << name << " could not be found" << std::endl;
    }

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