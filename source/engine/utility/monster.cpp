#include <engine/engine.hpp>

namespace Engine {
void
Engine::createMonsters() {
    // Function used to check for walls
    auto checkWall = [&](const SDL_FPoint& point, const int& threshold, const Directions& direction) {
        return movementWalls(point, threshold, direction);
    };
    auto& playerCenter = mPlayer->getPlayerCenter();

    mMonsters[Monster::Type::CAVE_CRAWLER] = new Monster::CaveCrawler(75, 0.2f, playerCenter, checkWall);
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, *GET_ANIMATED("CaveCrawlerNorth"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::MOVE, Directions::EAST, *GET_ANIMATED("CaveCrawlerEast"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, *GET_ANIMATED("CaveCrawlerSouth"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::MOVE, Directions::WEST, *GET_ANIMATED("CaveCrawlerWest"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, *GET_ANIMATED("CaveCrawlerNorth"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::IDLE, Directions::EAST, *GET_ANIMATED("CaveCrawlerEast"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, *GET_ANIMATED("CaveCrawlerSouth"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::IDLE, Directions::WEST, *GET_ANIMATED("CaveCrawlerWest"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::DYING, Directions::ALL, *GET_ANIMATED("CaveCrawlerDead"));

    mMonsters[Monster::Type::SLIME_BLUE] = new Monster::Slime(30, 0.5, playerCenter, checkWall);
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, *GET_ANIMATED("SlimeBlueNorth"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::MOVE, Directions::EAST, *GET_ANIMATED("SlimeBlueEast"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, *GET_ANIMATED("SlimeBlueSouth"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::MOVE, Directions::WEST, *GET_ANIMATED("SlimeBlueWest"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, *GET_ANIMATED("SlimeBlueNorth"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::IDLE, Directions::EAST, *GET_ANIMATED("SlimeBlueEast"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, *GET_ANIMATED("SlimeBlueSouth"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::IDLE, Directions::WEST, *GET_ANIMATED("SlimeBlueWest"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::DYING, Directions::ALL, *GET_ANIMATED("SlimeBlueDead"));

    mMonsters[Monster::Type::SLIME_GREEN] = new Monster::Slime(30, 0.5, playerCenter, checkWall);
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, *GET_ANIMATED("SlimeGreenNorth"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::MOVE, Directions::EAST, *GET_ANIMATED("SlimeGreenEast"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, *GET_ANIMATED("SlimeGreenSouth"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::MOVE, Directions::WEST, *GET_ANIMATED("SlimeGreenWest"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, *GET_ANIMATED("SlimeGreenNorth"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::IDLE, Directions::EAST, *GET_ANIMATED("SlimeGreenEast"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, *GET_ANIMATED("SlimeGreenSouth"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::IDLE, Directions::WEST, *GET_ANIMATED("SlimeGreenWest"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::DYING, Directions::ALL, *GET_ANIMATED("SlimeGreenDead"));

    mMonsters[Monster::Type::SLIME_PURPLE] = new Monster::Slime(30, 0.5, playerCenter, checkWall);
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, *GET_ANIMATED("SlimePurpleNorth"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::MOVE, Directions::EAST, *GET_ANIMATED("SlimePurpleEast"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, *GET_ANIMATED("SlimePurpleSouth"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::MOVE, Directions::WEST, *GET_ANIMATED("SlimePurpleWest"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, *GET_ANIMATED("SlimePurpleNorth"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::IDLE, Directions::EAST, *GET_ANIMATED("SlimePurpleEast"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, *GET_ANIMATED("SlimePurpleSouth"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::IDLE, Directions::WEST, *GET_ANIMATED("SlimePurpleWest"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::DYING, Directions::ALL, *GET_ANIMATED("SlimePurpleDead"));

    mMonsters[Monster::Type::SLIME_RED] = new Monster::Slime(30, 0.5, playerCenter, checkWall);
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, *GET_ANIMATED("SlimeRedNorth"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::MOVE, Directions::EAST, *GET_ANIMATED("SlimeRedEast"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, *GET_ANIMATED("SlimeRedSouth"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::MOVE, Directions::WEST, *GET_ANIMATED("SlimeRedWest"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, *GET_ANIMATED("SlimeRedNorth"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::IDLE, Directions::EAST, *GET_ANIMATED("SlimeRedEast"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, *GET_ANIMATED("SlimeRedSouth"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::IDLE, Directions::WEST, *GET_ANIMATED("SlimeRedWest"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::DYING, Directions::ALL, *GET_ANIMATED("SlimeRedDead"));
}

};