#include <monster/slime.hpp>
#include <utility/trigonometry.hpp>

namespace Monster {
Slime::Slime(const int&                                                         health,
             const float&                                                       velocity,
             const float&                                                       radius,
             SDL_FPoint&                                                        playerCenter,
             std::function<bool(const SDL_FPoint&, const float&, const float&)> checkWalls)
  : mRadius(radius)
  , BaseMonster(health, velocity, "Slime", playerCenter, checkWalls) {}

Slime::~Slime() {}

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

void
Slime::interact() {
    switch (mState) {
        case Objects::IDLE:
            if (Utility::getDistance(mMonsterCenter, mPlayerCenter) <= mRadius) {
                mState = Objects::MOVE;
                mTicks = 0;
            }

            break;

        case Objects::MOVE: {
            if (Utility::getDistance(mMonsterCenter, mPlayerCenter) > mRadius) {
                mState = Objects::IDLE;
                mTicks = 0;
            } else {
                const auto angle    = Utility::getAngle(mPlayerCenter, mMonsterCenter);
                const auto position = Utility::calculateVector(angle, mVelocity);
                if (fCheckWalls(mMonsterCenter, position.x, position.y)) {
                    mMonsterCenter.x += position.x;
                    mMonsterCenter.y += position.y;
                    mMonsterPosition.x += position.x;
                    mMonsterPosition.y += position.y;
                }
            }
        } break;
    }
    updateReferences();
}
}