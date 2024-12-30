#include <npc/cow.hpp>

namespace NPC {
Cow::Cow(std::function<bool(const SDL_FPoint&, const float&, const float&)> checkWalls)
  : BaseNPC(26,24,checkWalls) {}

Cow::~Cow() = default;

BaseNPC*
Cow::spawn(const float& x, const float& y) const{
    const auto xPos = x * 16.0f;
    const auto yPos = y * 16.0f;
    auto obj = new Cow(*this);
    obj->mNPCPosition.x = xPos + (16 - mNPCWidth) / 2.0f;
    obj->mNPCPosition.y = yPos + (16 - mNPCHeight) / 2.0f;
    obj->mNPCPosition.w = mNPCWidth;
    obj->mNPCPosition.h = mNPCHeight;
    obj->mNPCCenter.x = xPos + (mNPCWidth / 2.0f);
    obj->mNPCCenter.y = xPos + (mNPCHeight / 2.0f);
    return obj;
}

void
Cow::interact() {
    static float distance;
    switch (mState) {
        case Objects::IDLE: {
            auto  dir        = getRandomDirection();
            auto  tempCenter = mNPCCenter;
            bool  done       = false;
            float x          = 0.0f;
            float y          = 0.0f;
            do {
                switch (dir) {
                    case North:
                        y = -2.0f;
                        x = 0.0f;
                        break;
                    case East:
                        x = 2.0f;
                        y = 0.0f;
                        break;
                    case South:
                        y = 2.0f;
                        x = 0.0f;
                        break;
                    case West:
                        x = -2.0f;
                        y = 0.0f;
                        break;
                    default:
                        break;
                }

                // Randomize a new direction
                while (fCheckWalls(tempCenter, x, y)) {
                    switch (dir) {
                        case North:
                            tempCenter.y -= 2.0f;
                            break;
                        case East:
                            tempCenter.x += 2.0f;
                            break;
                        case South:
                            tempCenter.y += 2.0f;
                            break;
                        case West:
                            tempCenter.x -= 2.0f;
                            break;
                        default:
                            break;
                    }
                    distance += 2.0f;
                    done = true;
                    if (distance >= 8.0f)
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
                case North:
                    if (fCheckWalls(mNPCCenter, 0, -mVelocity))
                        updatePosition(0.0f, -mVelocity);
                    else
                        mState = Objects::IDLE;
                    break;
                case East:
                    if (fCheckWalls(mNPCCenter, mVelocity, 0.0f))
                        updatePosition(mVelocity, 0.0f);
                    else
                        mState = Objects::IDLE;
                    break;
                case South:
                    if (fCheckWalls(mNPCCenter, 0.0f, mVelocity))
                        updatePosition(0.0f, mVelocity);
                    else
                        mState = Objects::IDLE;
                    break;
                case West:
                    if (fCheckWalls(mNPCCenter, -mVelocity, 0.0f))
                        updatePosition(-mVelocity, 0.0f);
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