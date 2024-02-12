#pragma once
#include <utility>

namespace Utility{
/***
 * @brief Calculate the new position based on angle and velocity
 * @param angle Angle the object is moving. 0 degree is equal to 3 o'clock
 * @param velocity Velocity of object in pixels
 */
template <typename T>
std::pair<T,T> calculateVector(const T& angle, const T& velocity, const T&x, const T& y){
    auto angleRadians = angle * M_PI / 180.0;

    auto deltaX = velocity * cos(angleRadians);
    auto deltaY = velocity * sin(angleRadians);
    return std::make_pair(static_cast<T>(deltaX), static_cast<T>(deltaY));
}


/***
 * @brief Calculate the angle between 2 points in a coordinate system
 * @return The angle
 */
float calculateAngle(const std::pair<float,float>& p1,const std::pair<float,float>& p2);
float calculateAngle(const float& x1, const float& y1, const float& x2, const float& y2);


}