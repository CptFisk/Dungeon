#pragma once
#include <utility>

namespace Utility {
/***
 * @brief Calculate the new position based on angle and velocity
 * @param angle Angle the object is moving. 0 degree is equal to 3 o'clock
 * @param velocity Velocity of object in pixels
 */
template<typename T>
std::pair<T, T>
calculateVector(const T& angle, const T& velocity, const T& x, const T& y) {
    auto angleRadians = angle * M_PI / 180.0;

    auto deltaX = velocity * cos(angleRadians);
    auto deltaY = velocity * sin(angleRadians);
    return std::make_pair(static_cast<T>(deltaX), static_cast<T>(deltaY));
}

/***
 * @brief Calculate the angle between 2 points in a coordinate system
 * @return The angle
 */
template<typename T>
T
calculateAngle(const std::pair<T, T>& p1, const std::pair<T, T>& p2) {
    return calculateAngle(p1.first, p1.second, p2.first, p2.second);
}
template<typename T>
T
calculateAngle(const T& x1, const T& y1, const T& x2, const T& y2) {
    auto deltaX = x2 - x1;
    auto deltaY = y2 - y1;

    auto angleRadians = atan2(deltaY, deltaX);
    auto angleDegrees = angleRadians * 180 / M_PI;

    // Convert negative angles to positive equivalent
    if (angleDegrees < 0)
        angleDegrees += 360;

    return static_cast<T>(angleDegrees);
}

}