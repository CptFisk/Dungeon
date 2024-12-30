#include <engine/engine.hpp>

namespace Engine {

void
Engine::createNPC() {
    mNPCs[NPC::Type::COW] = new NPC::Cow(
      [&](const SDL_FPoint& point, const float& x, const float& y) { return wallCheck(point, x, y, WALL_OBSTACLE_NPC, true); });
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::MOVE, Orientation::North, GET_ANIMATED("Cow1North"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::MOVE, Orientation::East, GET_ANIMATED("Cow1East"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::MOVE, Orientation::South, GET_ANIMATED("Cow1South"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::MOVE, Orientation::West, GET_ANIMATED("Cow1West"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::IDLE, Orientation::North, GET_ANIMATED("Cow1NorthIdle"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::IDLE, Orientation::East, GET_ANIMATED("Cow1EastIdle"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::IDLE, Orientation::South, GET_ANIMATED("Cow1SouthIdle"));
    mNPCs[NPC::Type::COW]->addAnimatedTexture(Objects::IDLE, Orientation::West, GET_ANIMATED("Cow1WestIdle"));
}
}