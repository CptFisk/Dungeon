#pragma once
namespace Utility{
/***
 * @brief Calculate the new position based on angle and velocity
 * @param angle Angle the object is moving. 0 degree is equal to 3 o'clock
 * @param velocity Velocity of object in pixels
 * @param x Reference to x-coord
 * @param y Reference to y-coord
 */
void calculateVector(const float& angle, const float& velocity, float &x, float &y);
}