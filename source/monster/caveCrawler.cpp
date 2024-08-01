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
    static float distance;
    switch (mState) {
        case Objects::IDLE: {
            auto dir        = getRandomDirection();
            auto tempCenter = mMonsterCenter;
            bool done       = false;
            do {
                // Randomize a new direction
                while (fCheckWalls(tempCenter, 16.0f, dir)) {
                    switch (dir) {
                        case NORTH:
                            tempCenter.y -= 16.0f;
                            break;
                        case EAST:
                            tempCenter.x += 16.0f;
                            break;
                        case SOUTH:
                            tempCenter.y += 16.0f;
                            break;
                        case WEST:
                            tempCenter.x -= 16.0f;
                            break;
                    }
                    distance += 16.0f;
                    done = true;
                    if(distance >= 48.0f)
                        break;  //So we dont walk in eternity
                }
                // Invalid direction, try a new one
                if (!done)
                    dir = getRandomDirection();

            } while (!done);
            mState     = Objects::MOVE;
            mDirection = dir;
            updateReferences();
        } break;

        case Objects::MOVE:
            switch (mDirection) {
                case NORTH:
                    updatePosition(0.0f, -mVelocity);
                    break;
                case EAST:
                    updatePosition(mVelocity, 0.0f);
                    break;
                case SOUTH:
                    updatePosition(0.0f, mVelocity);
                    break;
                case WEST:
                    updatePosition(-mVelocity, 0.0f);
                    break;
            }
            if ((distance -= mVelocity) <= 0) {
                mState = Objects::IDLE;
            };
            updateReferences();
            break;
    }
}
}