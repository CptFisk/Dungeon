#include <iostream>
#include <monster/beanMan.hpp>
#include <utility/trigonometry.hpp>

namespace Monster {
BeanMan::BeanMan(const float&                                                            width,
                 const float&                                                            height,
                 const int&                                                              health,
                 const float&                                                            velocity,
                 const std::string& name,
                 const std::optional<std::unordered_map<std::string, std::any>>& defaults)
  : mMonsterWidth(width)
  , mMonsterHeight(height)
  , mReload(0)
  , mDelay(0)
  , BaseMonster(health, velocity, name, defaults) {}

BeanMan::~BeanMan() = default;

void
BeanMan::attack(){

}

BaseMonster*
BeanMan::spawn(const float& x, const float& y) const {
    const auto xPos         = x * 16.0f; // One square is 16 pixels
    const auto yPos         = y * 16.0f; // One square is 16 pixels
    auto       obj          = new BeanMan(*this);
    obj->mMonsterPosition.x = xPos + FLOAT((16 - mMonsterWidth) / 2);
    obj->mMonsterPosition.y = yPos + FLOAT((16 - mMonsterHeight) / 2);
    obj->mMonsterPosition.w = mMonsterWidth;
    obj->mMonsterPosition.h = mMonsterHeight;
    obj->mMonsterCenter.x   = xPos + (mMonsterWidth / 2.0f);
    obj->mMonsterCenter.y   = yPos + (mMonsterHeight / 2.0f);
    obj->luaFile = this->luaFile;
    obj->mRetains           = mRetains;
    return obj;
}
/*
void
BeanMan::interact() {
    switch (mState) {
        case Objects::IDLE:
            if (Utility::getDistance(mMonsterCenter, mPlayerCenter) < 3.0f) {
                mState = Objects::MOVE;
                mTicks = 0;
            } else if (mReload == 0 && // We don´t want a machine gun...
                       Utility::getDistance(mMonsterCenter, mPlayerCenter) > 3.0f &&
                       Utility::getDistance(mMonsterCenter, mPlayerCenter) < 5.0f) {

                mState = Objects::ATTACK; // Go nuts
            }
            break;

        case Objects::MOVE:
            if (Utility::getDistance(mMonsterCenter, mPlayerCenter) > 4.5f) {
                mState = Objects::IDLE;
                mTicks = 0;
            } else {
                auto angle          = Utility::getAngle(mPlayerCenter, mMonsterCenter);
                angle               = FLOAT((INT(angle + 180.0) % 360));
                const auto position = Utility::calculateVector(angle, mVelocity);
                if (fCheckWalls(mMonsterCenter, position.x, position.y)) {
                    mMonsterCenter.x += position.x;
                    mMonsterCenter.y += position.y;
                    mMonsterPosition.x += position.x;
                    mMonsterPosition.y += position.y;
                }
            }
            break;

        case Objects::ATTACK:
            if (fcProjectiles(mMonsterCenter, Utility::getAngle(mPlayerCenter, mMonsterCenter), mDelay)) {
                mState  = Objects::IDLE;
                mReload = 100;
                mDelay  = 0;
            }
            mDelay++;
    }
    mReload = std::max(0, --mReload);
    updateReferences();
}
 */

/*
SDL_FPoint
BeanMan::wobbleMovement(const double& angle, const float& velocity) {
    static float t1        = 0.0f;
    const double amplitude = 1;
    const double freq      = 0.2;

    const auto angleRadians = angle * M_PI / 180.0f;

    // Calculate forward movement (straight line based on velocity and angle)
    const auto dx = velocity * cos(angleRadians);
    const auto dy = velocity * sin(angleRadians);

    // Calculate the wobble component
    const auto wobble  = amplitude * sin(freq * t1 * 2 * M_PI);
    const auto wobbleX = wobble * sin(angleRadians); // Perpendicular in X direction
    const auto wobbleY = wobble * cos(angleRadians); // Perpendicular in Y direction

    t1 += 0.01f;

    // Calculate the total offset vector (forward + wobble)
    float totalX = dx + wobbleX;
    float totalY = dy + wobbleY;

    // Calculate the magnitude of the resulting vector
    float magnitude = sqrt(totalX * totalX + totalY * totalY);

    // If the magnitude exceeds the velocity, scale the vector down to match the velocity
    if (magnitude > velocity) {
        float scale = velocity / magnitude; // Scale factor to normalize the speed
        totalX *= scale;
        totalY *= scale;
    }

    // Return the scaled (or unmodified) offset
    return SDL_FPoint{ totalX, totalY };
}
 */

}