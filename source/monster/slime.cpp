#include <monster/slime.hpp>
#include <utility/trigonometry.hpp>

namespace Monster {
Slime::Slime(const int&                                                            health,
             const float&                                                          velocity,
             SDL_FPoint&                                                           playerCenter,
             std::function<bool(const SDL_FPoint&, const int&, const Directions&)> checkWalls)
  : mTicks(0)
  , IDLE(75)
  , MOVE(300)
  , BaseMonster(health, velocity, playerCenter, checkWalls) {}

Slime::~Slime() {}

BaseMonster*
Slime::spawn(const float& x, const float& y) const {
    const auto xPos         = x * 16.0f; // One square is 16 pixels
    const auto yPos         = y * 16.0f; // One square is 16 pixels
    auto obj                = new Slime(*this);

    obj->mMonsterPosition.x = xPos + FLOAT((16 - MONSTER_WIDTH) / 2);
    obj->mMonsterPosition.y = yPos + FLOAT((16 - MONSTER_HEIGHT) / 2);
    obj->mMonsterPosition.w = MONSTER_WIDTH;
    obj->mMonsterPosition.h = MONSTER_HEIGHT;
    obj->mMonsterCenter.x   = xPos + (MONSTER_WIDTH / 2.0f);
    obj->mMonsterCenter.y   = yPos + (MONSTER_HEIGHT / 2.0f);
    return obj;
}

void
Slime::interact() {
    /*
    if (mState == Objects::IDLE) {
        if (mTicks++ > IDLE) {
            mState = Objects::MOVE;
            mTicks = 0;
        }
    } else if (mState == Objects::MOVE) {
        auto angle = Utility::calculateMovement(mMonsterPosition.x, mMonsterPosition.y, mPlayerCenter.x, mPlayerCenter.y, mVelocity);
        mMonsterPosition.x += angle.first;
        mMonsterPosition.y += angle.second;
        if (mTicks++ > MOVE) {
            mState = Objects::IDLE;
            mTicks = 0;
        }

    }
     */
    updateReferences();
}
}