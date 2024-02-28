#include <monster/slime.hpp>
#include <utility/trigonometry.hpp>

namespace Monster {
Slime::Slime(const int& health, const float& velocity, SDL_FRect* playerPosition)
  : BaseMonster(health, velocity, playerPosition) {}

Slime::~Slime() {}

BaseMonster*
Slime::spawn(const float& x, const float& y) const {
    auto obj                = new Slime(*this);
    obj->mMonsterPosition.x = x;
    obj->mMonsterPosition.y = y;
    return obj;
}

void
Slime::move(Directions direction) {
    mAction = Objects::MOVE;
    auto angle = Utility::calculateMovement(mMonsterPosition.x, mMonsterPosition.y, pPlayerPosition->x, pPlayerPosition->y, mVelocity);
    mMonsterPosition.x += angle.first;
    mMonsterPosition.y += angle.second;
    updateReferences();
}
}