#include <engine/engine.hpp>
#include <monster/caveCrawler.hpp>
namespace Monster {
CaveCrawler::CaveCrawler(const int&                                                            health,
                         const float&                                                          velocity,
                         SDL_FPoint&                                                           playerCenter,
                         std::function<bool(const SDL_FPoint&, const int&, const Directions&)> checkWalls)
  : mTicks(0)
  , BaseMonster(health, velocity, playerCenter, checkWalls) {}

CaveCrawler::~CaveCrawler() = default;

BaseMonster*
CaveCrawler::spawn(const float& x, const float& y) const {
    const auto xPos         = x * 16.0f; // One square is 16 pixels
    const auto yPos         = y * 16.0f; // One square is 16 pixels
    auto       obj          = new CaveCrawler(*this);
    obj->mMonsterPosition.x = xPos - FLOAT((INT(MONSTER_WIDTH) % 16) / 2);
    obj->mMonsterPosition.y = yPos - FLOAT((INT(MONSTER_HEIGHT) % 16) / 2);
    obj->mMonsterPosition.w = MONSTER_WIDTH;
    obj->mMonsterPosition.h = MONSTER_HEIGHT;
    obj->mMonsterCenter.x   = xPos + 9;
    obj->mMonsterCenter.y   = yPos + 9;
    return obj;
}

void
CaveCrawler::interact() {
    if (mState == Objects::IDLE) {
        if (fCheckWalls(mMonsterCenter, 16.0, NORTH)) {
            mState = Objects::MOVE;
        }
    }
    if (mState == Objects::MOVE) {
        mMonsterPosition.y += 0.1;
    }
}
}