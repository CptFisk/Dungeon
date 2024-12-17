#include <monster/slime.hpp>
#include <utility/trigonometry.hpp>

namespace Monster {
Slime::Slime(const int&                                                         health,
             const float&                                                       velocity,
             const float&                                                       radius,
             const std::string& name)
  : mRadius(radius)
  , BaseMonster(health, velocity, name) {}

Slime::~Slime() {}

void
Slime::attack() {}

BaseMonster*
Slime::spawn(const float& x, const float& y) const {
    const auto xPos = x * 16.0f; // One square is 16 pixels
    const auto yPos = y * 16.0f; // One square is 16 pixels
    auto       obj  = new Slime(*this);

    obj->mMonsterPosition.x = xPos + FLOAT((16 - MONSTER_WIDTH) / 2);
    obj->mMonsterPosition.y = yPos + FLOAT((16 - MONSTER_HEIGHT) / 2);
    obj->mMonsterPosition.w = MONSTER_WIDTH;
    obj->mMonsterPosition.h = MONSTER_HEIGHT;
    obj->mMonsterCenter.x   = xPos + (MONSTER_WIDTH / 2.0f);
    obj->mMonsterCenter.y   = yPos + (MONSTER_HEIGHT / 2.0f);
    obj->luaFile = this->luaFile;
    return obj;
}
}