#include <algorithm>
#include <common/math.hpp>
#include <engine/engine.hpp>
#include <engine/helper/functions.hpp>
#include <file/engineFile.hpp>
#include <global.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <utility/bits.hpp>
#include <utility/math.hpp>
#include <utility/textures.hpp>
#include <utility/trigonometry.hpp>

namespace Engine {

void
Engine::loadLevel(const std::string& filename) {
    // If a map is loaded, unload it.
    if (mLevelLoaded)
        clearLoadedLevel();
    const auto start = std::chrono::high_resolution_clock::now();
    auto       data  = File::readEngineData("levels/" + filename, pRenderer);
    const auto time  = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << "Loading time: " << time.count() << " ms" << std::endl;
    mMapCoordinate = data.Header.MapCoordinate;
    mOnExit        = data.Header.OnExit;

    mColour = data.Header.Colour;
    mOnLoad = data.Header.OnLoad;
    mOnLoad = data.Header.OnExit;

    mSegments.Bottom.Layers      = data.Layers.Bottom;
    mSegments.Bottom.Position    = SDL_FRect{ 0, 0, 2048, 2048 };
    mSegments.CurrentLayerBottom = 0;
    mSegments.MaxLayerBottom     = UINT8(data.Layers.Bottom.size());

    mSegments.Top.Layers      = data.Layers.Top;
    mSegments.Top.Position    = SDL_FRect{ 0, 0, 2048, 2048 };
    mSegments.CurrentLayerTop = 0;
    mSegments.MaxLayerTop     = UINT8(data.Layers.Top.size());

    mSegments.Lightning.Layers      = data.Layers.Lightning;
    mSegments.Lightning.Position    = SDL_FRect{ 0, 0, 2048, 2048 };
    mSegments.CurrentLayerLightning = 0;
    mSegments.MaxLayerLightning     = UINT8(data.Layers.Lightning.size());

    // Set background colors
    mColour.BackgroundRed   = data.Header.Colour.BackgroundRed;
    mColour.BackgroundGreen = data.Header.Colour.BackgroundGreen;
    mColour.BackgroundBlue  = data.Header.Colour.BackgroundBlue;

    int pos      = 0;
    levelObjects = std::vector<std::bitset<8>>(MAP_SIZE);
    for (auto& tile : data.Tiles) {
        const auto& [x, y] = Common::getCoords(pos, MAP_WIDTH, MAP_WIDTH);
        if (tile.test(Common::TileType::OBSTACLE)) {
            levelObjects[pos].set(Common::TileType::OBSTACLE);
        }
        // Add walls
        if (tile.test(Common::TileType::WALL)) {
            levelObjects[pos].set(Common::TileType::WALL);
        }
        // Add transportation up
        if (tile.test(Common::TileType::UP)) {
            if (mMapCoordinate.Z > 0) {
                const auto origin = mMapCoordinate;
                // Reduce our Z-layer by one
                Common::type3DMapCoordinate level(origin.X, origin.Y, origin.Z + 1);
                Common::type2DMapCoordinate destination(x, y + 1);
                warp[pos] = new Objects::Warp(level, destination);
            } else {
                std::cerr << "Not a valid coordinate" << std::endl;
            }
        }
        // Add transportation down
        if (tile.test(Common::TileType::DOWN)) {
            if (mMapCoordinate.Z > 0) {
                const auto origin = mMapCoordinate;
                // Reduce our Z-layer by one
                Common::type3DMapCoordinate level(origin.X, origin.Y, origin.Z - 1);
                Common::type2DMapCoordinate destination(x, y + 1);
                warp[pos] = new Objects::Warp(level, destination);
            } else {
                std::cerr << "Not a valid coordinate" << std::endl;
            }
        }
        if (Utility::isAnyBitSet(tile, std::bitset<32>(MONSTER_BITS))) {
            // Extract the id
            auto monsterId = static_cast<Monster::Type>(Utility::getBitValue<32, int>(tile, 10, 17));
            mActiveMonsters.push_back(mMonsters[monsterId]->spawn(x, y));
        }
        if (Utility::isAnyBitSet(tile, std::bitset<32>(NPC_BITS))) {
            auto npcId = static_cast<NPC::Type>(Utility::getBitValue<32, int>(tile, 18, 23));
            mActiveNPCs.push_back(mNPCs[npcId]->spawn(x, y));
            mActiveNPCs.back()->setDirection(North);
        }
        pos++;
    }

    mLevelLoaded = true;
    // Run all startup functions
    for (const auto& name : data.Header.OnLoad) {
        auto function = getExternalFunction(name);
        ASSERT_WITH_MESSAGE(!function, "Function: " << name << " could not load")
        function();
    }
}

bool
Engine::wallCheck(const SDL_FPoint& other, const float& x, const float& y, const long unsigned int& mask, bool playerCheck) {

    auto posX = INT(other.x + x);
    auto posY = INT(other.y + y);

    // We divide by 16 to get a coordinate rather than pixel
    const auto index = Common::getIndex(posX / 16, posY / 16, MAP_WIDTH);
    if (!index.has_value()) {
        return false;
    }

    if (Utility::isAnyBitSet(levelObjects[index.value()], std::bitset<8>(mask)))
        return false;
    if(playerCheck && Utility::isOverlapping(other, *pPlayerPosition))
        return false;
    return true;
}

bool
Engine::wallCheck(const float& x, const float& y, const long unsigned int& mask) {
    auto posX = static_cast<int>(x);
    auto posY = static_cast<int>(y);
    const auto index = Common::getIndex(posX / 16, posY / 16, MAP_WIDTH);
    if(!index.has_value())
        return false;
    if (Utility::isAnyBitSet(levelObjects[index.value()], std::bitset<8>(mask)))
        return false;
    return true;
}

bool
Engine::movement(const SDL_FPoint& other,const SDL_FPoint& vector, const double& angle) {
    auto pos = Utility::addFPoint(other, vector);
    if (pos.x < 0 || pos.y < 0)
        return false; // No need to evaluate more
    auto playerX = INT(pos.x / 16.0f);
    auto playerY = INT(pos.y / 16.0f);

    const auto index = Common::getIndex(playerX, playerY, MAP_WIDTH);
    if (!index.has_value())
        return false;
    if ((levelObjects[index.value()].test(Common::TileType::WALL) || levelObjects[index.value()].test(Common::TileType::OBSTACLE)))
        return false;
    auto it = warp.find(index.value());
    if (it != warp.end()) {
        auto       object = it->second;
        const auto level  = object->getLevel();
        if (level != mMapCoordinate) {
            const auto destination = object->getDestination(); // Need to store before swapping map
            loadLevel(object->getLevel().toString() + ".lvl");
            mPlayer->spawn(destination);
            mPerspective->center(pPlayerPosition->x + 8.0f, pPlayerPosition->y + 8.0f);
        } else {
            std::cout << "Swap level" << std::endl;
        }
        return false;
    }
    /*
    for (const auto& door : doors) {
        if (!door->isPassable()) {
            if (Utility::isColliding(other, door->getPosition(), direction))
                return false;
        }
    }
     */
    return true;
}

bool
Engine::movement(const SDL_FPoint& other, const Orientation& direction) {
    return movement(SDL_FRect{other.x, other.y, 1.0f, 1.0f}, direction);
}

bool
Engine::movement(const SDL_FRect& other, const Orientation& direction) {
    auto pos = other;

    const float threshold = 1.0f;
    switch (direction) {
        case North:
            pos.y -= threshold;
            break;
        case East:
            pos.x += threshold;
            break;
        case South:
            pos.y += threshold;
            break;
        case West:
            pos.x -= threshold;
            break;
        case All:
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
    if ((levelObjects[index.value()].test(Common::TileType::WALL) || levelObjects[index.value()].test(Common::TileType::OBSTACLE)))
        return false;
    auto it = warp.find(index.value());
    if (it != warp.end()) {
        auto       object = it->second;
        const auto level  = object->getLevel();
        if (level != mMapCoordinate) {
            const auto destination = object->getDestination(); // Need to store before swapping map
            loadLevel(object->getLevel().toString() + ".lvl");
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
    for (const auto& name : mOnExit) {
        auto function = getExternalFunction(name);
        if (function)
            function();
        else
            std::cerr << "Function: " << name << " could not be found" << std::endl;
    }
    // Kill and remove all cute monsters
    for (auto monster : mActiveMonsters)
        delete monster;
    for (auto npc : mActiveNPCs)
        delete npc;
    mActiveMonsters.clear();
    mActiveNPCs.clear();
    // Reset all values
    mLevelLoaded   = false;
    mMapCoordinate = {};
    mColour        = {};
    mFilename      = {};

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