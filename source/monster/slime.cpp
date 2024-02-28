#include <monster/slime.hpp>
#include <utility/trigonometry.hpp>

namespace Monster {
Slime::Slime(const int& health, const float& velocity, SDL_FRect* playerPosition)
  : mTicks(0)
  , IDLE(75)
  , MOVE(300)
  , BaseMonster(health, velocity, playerPosition) {}

Slime::~Slime() {}

BaseMonster*
Slime::spawn(const float& x, const float& y) const {

    auto obj                = new Slime(*this);
    obj->mMonsterPosition.x = x;
    obj->mMonsterPosition.y = y;
    return obj;
}

void
Slime::move() {
    if (mAction == Objects::IDLE) {
        if (mTicks++ > IDLE) {
            mAction = Objects::MOVE;
            mTicks  = 0;
        }
    } else {
        auto angle = Utility::calculateMovement(mMonsterPosition.x, mMonsterPosition.y, pPlayerPosition->x, pPlayerPosition->y, mVelocity);
        mMonsterPosition.x += angle.first;
        mMonsterPosition.y += angle.second;
        if(mTicks++ > MOVE){
            mAction = Objects::IDLE;
            mTicks = 0;
        }
        updateReferences();
    }
}
}