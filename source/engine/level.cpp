#include <algorithm>
#include <common/math.hpp>
#include <engine/engine.hpp>
#include <engine/helper/functions.hpp>
#include <global.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <utility/bits.hpp>
#include <utility/math.hpp>
#include <utility/textures.hpp>
namespace Engine {

void
Engine::loadLevel(const std::string& filename) {
    // If a map is loaded, unload it.
    if (mLevelLoaded)
        clearLoadedLevel();

    auto data = Level::readLevelData("levels/" + filename);
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
    createSegments(mSegments.Lightning, LIGHT_ANIMATION_FRAMES, mSegments.MaxLayerLightning);
    setSegmentAlpha(mSegments.Lightning, SDL_BLENDMODE_MUL, 0);
    int pos = 0;

    levelObjects = std::vector<std::bitset<8>>(MAP_SIZE);

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

        if (((it->Type.test(Level::TileType::BASE_TEXTURE) || it->Type.test(Level::TileType::TOP_TEXTURE)) && !it->Base.empty())) {
            const auto id    = INT(it->Base.front());
            const auto asset = data.Assets.Assets[id];
            addToSegment(mSegments.Bottom, pos, asset);

            it->Base.erase(it->Base.begin()); // Remove this element, it has been displayed

            if (!it->Base.empty())
                layersLeft = true; // There is more
        }
        // Overlay
        if (it->Type.test(Level::TileType::TOP_TEXTURE) && !it->Top.empty()) {
            const auto id    = INT(it->Top.front());
            const auto asset = data.Assets.Assets[id];
            addToSegment(mSegments.Top, pos, asset);
            it->Top.erase(it->Top.begin()); // Remove element
            if (!it->Top.empty())
                layersLeft = true;
        }
        // Add lightning effects
        if (Utility::isAnyBitSet((it->Type), std::bitset<32>(LIGHT_BITS))) {
            addLightning(it->Type, pos);
            Utility::resetBits(it->Type, std::bitset<32>(LIGHT_BITS));
        }
        // Add obstacles
        if (it->Type.test(Level::TileType::OBSTACLE)) {
            levelObjects[pos].set(Level::TileType::OBSTACLE);
            it->Type.reset(Level::TileType::OBSTACLE);
        }
        // Add walls
        if (it->Type.test(Level::TileType::WALL)) {
            levelObjects[pos].set(Level::TileType::WALL);
            it->Type.reset(Level::TileType::WALL); // Reset bit
        }
        // Add transportation up
        if (it->Type.test(Level::TileType::UP)) {
            const auto coords = Common::getCoords(pos, MAP_WIDTH, MAP_WIDTH);
            if (coords.has_value() && mHeader.MapCoordinate.Z > 0) {
                const auto origin  = mHeader.MapCoordinate;
                const auto& [x, y] = coords.value();
                // Reduce our Z-layer by one
                Level::type3DMapCoordinate level(origin.X, origin.Y, origin.Z + 1);
                Level::type2DMapCoordinate destination(x, y + 1);
                warp[pos] = new Objects::Warp(level, destination);
            } else {
                std::cerr << "Not a valid coordinate" << std::endl;
            }
            it->Type.reset(Level::TileType::UP);
        }
        // Add transportation down
        if (it->Type.test(Level::TileType::DOWN)) {
            const auto coords = Common::getCoords(pos, MAP_WIDTH, MAP_WIDTH);
            if (coords.has_value() && mHeader.MapCoordinate.Z > 0) {
                const auto origin  = mHeader.MapCoordinate;
                const auto& [x, y] = coords.value();
                // Reduce our Z-layer by one
                Level::type3DMapCoordinate level(origin.X, origin.Y, origin.Z - 1);
                Level::type2DMapCoordinate destination(x, y + 1);
                warp[pos] = new Objects::Warp(level, destination);
            } else {
                std::cerr << "Not a valid coordinate" << std::endl;
            }
            it->Type.reset(Level::TileType::DOWN); // Reset bit
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
Engine::movementWalls(const SDL_FPoint& other, const int& threshold, const Directions& direction) {
    auto posX = INT(other.x);
    auto posY = INT(other.y);
    switch (direction) {
        case NORTH:
            posY -= threshold;
            break;
        case EAST:
            posX += threshold;
            break;
        case SOUTH:
            posY += threshold;
            break;
        case WEST:
            posX -= threshold;
            break;
        default:
            break;
    }
    //We divide by 16 to get a coordinate rather than pixel
    const auto index = Common::getIndex(posX / 16, posY / 16, MAP_WIDTH);

    if (!index.has_value()) {
        return false;
    }
    if ((levelObjects[index.value()].test(Level::TileType::WALL) || levelObjects[index.value()].test(Level::TileType::OBSTACLE)))
        return false;
    return true;
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
    if ((levelObjects[index.value()].test(Level::TileType::WALL) || levelObjects[index.value()].test(Level::TileType::OBSTACLE)))
        return false;
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
    //Kill and remove all cute monsters
    for(auto monster : mActiveMonsters)
        delete monster;
    mActiveMonsters.clear();

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