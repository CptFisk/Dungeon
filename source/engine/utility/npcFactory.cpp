#include <engine/engine.hpp>

namespace Engine {

void
Engine::createNPC() {
    mNPCs[NPC::Type::COW] = new NPC::Cow([&](const SDL_FPoint& point, const float& x, const float& y) { return wallCheck(point, x, y, WALL_OBSTACLE_NPC); });
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::MOVE, Directions::NORTH, GET_ANIMATED("Cow1North"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::MOVE, Directions::EAST, GET_ANIMATED("Cow1East"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::MOVE, Directions::SOUTH, GET_ANIMATED("Cow1South"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::MOVE, Directions::WEST, GET_ANIMATED("Cow1West"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::IDLE, Directions::NORTH, GET_ANIMATED("Cow1NorthIdle"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::IDLE, Directions::EAST, GET_ANIMATED("Cow1EastIdle"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::IDLE, Directions::SOUTH, GET_ANIMATED("Cow1SouthIdle"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::IDLE, Directions::WEST, GET_ANIMATED("Cow1WestIdle"));
}
}