#include <engine/engine.hpp>
#include <global.hpp>

namespace Engine {
void
Engine::createMonsters() {

    auto& playerCenter = mPlayer->getPlayerCenter();

    mMonsters[Monster::Type::CAVE_CRAWLER] =
      new Monster::CaveCrawler(75, 0.2f, playerCenter, [&](const SDL_FPoint& point, const float& x, const float& y) {
          return wallCheck(point, x, y, WALL_OBSTACLE);
      });
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, GET_ANIMATED("CaveCrawlerNorth"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::MOVE, Directions::EAST, GET_ANIMATED("CaveCrawlerEast"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, GET_ANIMATED("CaveCrawlerSouth"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::MOVE, Directions::WEST, GET_ANIMATED("CaveCrawlerWest"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, GET_ANIMATED("CaveCrawlerNorth"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::IDLE, Directions::EAST, GET_ANIMATED("CaveCrawlerEast"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, GET_ANIMATED("CaveCrawlerSouth"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::IDLE, Directions::WEST, GET_ANIMATED("CaveCrawlerWest"));
    mMonsters[Monster::Type::CAVE_CRAWLER]->addAnimatedTexture(Objects::DYING, Directions::ALL, GET_ANIMATED("CaveCrawlerDead"));

    mMonsters[Monster::Type::SLIME_BLUE] =
      new Monster::Slime(30, 0.2f, 8.0f, playerCenter, [&](const SDL_FPoint& point, const float& x, const float& y) {
          return wallCheck(point, x, y, WALL_OBSTACLE);
      });
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, GET_ANIMATED("SlimeBlueNorth"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::MOVE, Directions::EAST, GET_ANIMATED("SlimeBlueEast"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, GET_ANIMATED("SlimeBlueSouth"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::MOVE, Directions::WEST, GET_ANIMATED("SlimeBlueWest"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, GET_ANIMATED("SlimeBlueNorth"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::IDLE, Directions::EAST, GET_ANIMATED("SlimeBlueEast"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, GET_ANIMATED("SlimeBlueSouth"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::IDLE, Directions::WEST, GET_ANIMATED("SlimeBlueWest"));
    mMonsters[Monster::Type::SLIME_BLUE]->addAnimatedTexture(Objects::DYING, Directions::ALL, GET_ANIMATED("SlimeBlueDead"));

    mMonsters[Monster::Type::SLIME_GREEN] =
      new Monster::Slime(60, 0.25f, 7.0f, playerCenter, [&](const SDL_FPoint& point, const float& x, const float& y) {
          return wallCheck(point, x, y, WALL_OBSTACLE);
      });
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, GET_ANIMATED("SlimeGreenNorth"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::MOVE, Directions::EAST, GET_ANIMATED("SlimeGreenEast"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, GET_ANIMATED("SlimeGreenSouth"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::MOVE, Directions::WEST, GET_ANIMATED("SlimeGreenWest"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, GET_ANIMATED("SlimeGreenNorth"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::IDLE, Directions::EAST, GET_ANIMATED("SlimeGreenEast"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, GET_ANIMATED("SlimeGreenSouth"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::IDLE, Directions::WEST, GET_ANIMATED("SlimeGreenWest"));
    mMonsters[Monster::Type::SLIME_GREEN]->addAnimatedTexture(Objects::DYING, Directions::ALL, GET_ANIMATED("SlimeGreenDead"));

    mMonsters[Monster::Type::SLIME_PURPLE] =
      new Monster::Slime(90, 0.3f, 6.5f, playerCenter, [&](const SDL_FPoint& point, const float& x, const float& y) {
          return wallCheck(point, x, y, WALL_OBSTACLE);
      });
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, GET_ANIMATED("SlimePurpleNorth"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::MOVE, Directions::EAST, GET_ANIMATED("SlimePurpleEast"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, GET_ANIMATED("SlimePurpleSouth"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::MOVE, Directions::WEST, GET_ANIMATED("SlimePurpleWest"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, GET_ANIMATED("SlimePurpleNorth"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::IDLE, Directions::EAST, GET_ANIMATED("SlimePurpleEast"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, GET_ANIMATED("SlimePurpleSouth"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::IDLE, Directions::WEST, GET_ANIMATED("SlimePurpleWest"));
    mMonsters[Monster::Type::SLIME_PURPLE]->addAnimatedTexture(Objects::DYING, Directions::ALL, GET_ANIMATED("SlimePurpleDead"));

    mMonsters[Monster::Type::SLIME_RED] =
      new Monster::Slime(120, 0.5, 5.0f, playerCenter, [&](const SDL_FPoint& point, const float& x, const float& y) {
          return wallCheck(point, x, y, WALL_OBSTACLE);
      });
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, GET_ANIMATED("SlimeRedNorth"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::MOVE, Directions::EAST, GET_ANIMATED("SlimeRedEast"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, GET_ANIMATED("SlimeRedSouth"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::MOVE, Directions::WEST, GET_ANIMATED("SlimeRedWest"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, GET_ANIMATED("SlimeRedNorth"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::IDLE, Directions::EAST, GET_ANIMATED("SlimeRedEast"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, GET_ANIMATED("SlimeRedSouth"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::IDLE, Directions::WEST, GET_ANIMATED("SlimeRedWest"));
    mMonsters[Monster::Type::SLIME_RED]->addAnimatedTexture(Objects::DYING, Directions::ALL, GET_ANIMATED("SlimeRedDead"));

    mMonsters[Monster::Type::BEAN_MAN] = new Monster::BeanMan(
      12,           // Width
      13,           // Height
      110,          // Health
      0.2f,         // Velocity
      playerCenter, // Player position
      [&](const SDL_FPoint& point, const float& x, const float& y) {
          return wallCheck(point, x, y, WALL_OBSTACLE);
      }, // Function to check for walls
      [&](const SDL_FPoint& startPosition, const double& angle, int& delay) {
          if ((delay % 10) == 0) {
              createProjectile(false, GET_ANIMATED("PurpleBall"), nullptr, startPosition, angle, 50, 2, 10);
              if (delay == 30)
                  return true;
          }
          return false;
      });
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, GET_ANIMATED("BeanManNorth"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::MOVE, Directions::EAST, GET_ANIMATED("BeanManEast"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, GET_ANIMATED("BeanManSouth"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::MOVE, Directions::WEST, GET_ANIMATED("BeanManWest"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, GET_ANIMATED("BeanManNorth"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::IDLE, Directions::EAST, GET_ANIMATED("BeanManEast"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, GET_ANIMATED("BeanManSouth"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::IDLE, Directions::WEST, GET_ANIMATED("BeanManWest"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::ATTACK, Directions::NORTH, GET_ANIMATED("BeanManNorth"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::ATTACK, Directions::EAST, GET_ANIMATED("BeanManEast"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::ATTACK, Directions::SOUTH, GET_ANIMATED("BeanManSouth"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::ATTACK, Directions::WEST, GET_ANIMATED("BeanManWest"));
    mMonsters[Monster::Type::BEAN_MAN]->addAnimatedTexture(Objects::DYING, Directions::ALL, GET_ANIMATED("BeanManDead"));

    mMonsters[Monster::Type::BEAN_MAN_FLOWER] = new Monster::BeanMan(
      12,           // Width
      14,           // Height
      110,          // Health
      0.2f,         // Velocity
      playerCenter, // Player position
      [&](const SDL_FPoint& point, const float& x, const float& y) {
          return wallCheck(point, x, y, WALL_OBSTACLE);
      }, // Function to check for walls
      [&](const SDL_FPoint& startPosition, const double& angle, int& delay) {
          for (int i = 0; i <= 18; i++)
              createProjectile(false, GET_ANIMATED("PurpleBall"), nullptr, startPosition, i * 20, 200, 0.75f, 10);
          return true;
      });
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, GET_ANIMATED("BeanManFlowerNorth"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::MOVE, Directions::EAST, GET_ANIMATED("BeanManFlowerEast"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, GET_ANIMATED("BeanManFlowerSouth"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::MOVE, Directions::WEST, GET_ANIMATED("BeanManFlowerWest"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, GET_ANIMATED("BeanManFlowerNorth"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::IDLE, Directions::EAST, GET_ANIMATED("BeanManFlowerEast"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, GET_ANIMATED("BeanManFlowerSouth"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::IDLE, Directions::WEST, GET_ANIMATED("BeanManFlowerWest"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::ATTACK, Directions::NORTH, GET_ANIMATED("BeanManFlowerNorth"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::ATTACK, Directions::EAST, GET_ANIMATED("BeanManFlowerEast"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::ATTACK, Directions::SOUTH, GET_ANIMATED("BeanManFlowerSouth"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::ATTACK, Directions::WEST, GET_ANIMATED("BeanManFlowerWest"));
    mMonsters[Monster::Type::BEAN_MAN_FLOWER]->addAnimatedTexture(Objects::DYING, Directions::ALL, GET_ANIMATED("BeanManFlowerDead"));
}
};