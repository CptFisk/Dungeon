#include <engine/engine.hpp>
#include <monster/caveCrawler.hpp>
namespace Monster {
CaveCrawler::CaveCrawler(const int&                                                         health,
                         const float&                                                       velocity,
                         SDL_FPoint&                                                        playerCenter,
                         std::function<bool(const SDL_FPoint&, const float&, const float&)> checkWalls)
  : BaseMonster(health, velocity, "CaveCrawler", playerCenter, checkWalls) {}

CaveCrawler::~CaveCrawler() = default;

BaseMonster*
CaveCrawler::spawn(const float& x, const float& y) const {
    const auto xPos         = x * 16.0f; // One square is 16 pixels
    const auto yPos         = y * 16.0f; // One square is 16 pixels
    auto       obj          = new CaveCrawler(*this);
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
CaveCrawler::interact() {
    static float distance;
    switch (mState) {
        case Objects::IDLE: {
            auto  dir        = getRandomDirection();
            auto  tempCenter = mMonsterCenter;
            bool  done       = false;
            float x          = 0.0f;
            float y          = 0.0f;
            do {
                switch (dir) {
                    case NORTH:
                        y = -16.0f;
                        x = 0.0f;
                        break;
                    case EAST:
                        x = 16.0f;
                        y = 0.0f;
                        break;
                    case SOUTH:
                        y = 16.0f;
                        x = 0.0f;
                        break;
                    case WEST:
                        x = -16.0f;
                        y = 0.0f;
                        break;
                    default:
                        break;
                }

                // Randomize a new direction
                while (fCheckWalls(tempCenter, x, y)) {
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
                        default:
                            break;
                    }
                    distance += 16.0f;
                    done = true;
                    if (distance >= 48.0f)
                        break; // So we don't walk in eternity
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
                    if (fCheckWalls(mMonsterCenter, 0, -mVelocity))
                        setPosition(0.0f, -mVelocity);
                    else
                        mState = Objects::IDLE;
                    break;
                case EAST:
                    if (fCheckWalls(mMonsterCenter, mVelocity, 0.0f))
                        setPosition(mVelocity, 0.0f);
                    else
                        mState = Objects::IDLE;
                    break;
                case SOUTH:
                    if (fCheckWalls(mMonsterCenter, 0.0f, mVelocity))
                        setPosition(0.0f, mVelocity);
                    else
                        mState = Objects::IDLE;
                    break;
                case WEST:
                    if (fCheckWalls(mMonsterCenter, -mVelocity, 0.0f))
                        setPosition(-mVelocity, 0.0f);
                    else
                        mState = Objects::IDLE;
                    break;
                default:
                    break;
            }
            if ((distance -= mVelocity) <= 0) {
                mState = Objects::IDLE;
            };
            updateReferences();
            break;
        default:
            break;
    }
}
}