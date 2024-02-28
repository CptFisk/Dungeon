#include <monster/monster.hpp>

namespace Monster {
BaseMonster::BaseMonster(const int& health, const float& velocity)
  : mHealth(health)
  , mVelocity(velocity) {}

BaseMonster::~BaseMonster() = default;

bool
BaseMonster::damage(const int& damage) {
    if(mHealth -= damage <= 0)
        return true;
    return false;
}
}