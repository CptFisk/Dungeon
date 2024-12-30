#pragma once
#include <SDL.h>
#include <cmath>
#include <utility>
namespace Utility {
/***
 * @brief Calculate the new position based on angle and velocity
 * @param angle Angle the object is moving. 0 degree is equal to 3 o'clock
 * @param velocity Velocity of object in pixels
 */
inline SDL_FPoint
calculateVector(const double& angle, const float& velocity) {
    const auto angleRadians = angle * M_PI / 180.0f;
    const auto dx           = velocity * cos(angleRadians);
    const auto dy           = velocity * sin(angleRadians);
    return SDL_FPoint{ static_cast<float>(dx), static_cast<float>(dy) };
}

/***
 * @brief Calculate the angle between 2 points in a coordinate system
 * @return The angle as double
 */
inline constexpr double
getAngle(const float& ax, const float& ay, const SDL_FPoint& b) {
    const auto dx = ax - b.x;
    const auto dy = ay - b.y;

    const auto angleRadians = atan2(dy, dx);
    auto       angleDegrees = angleRadians * 180 / M_PI;

    // Convert negative angles to positive equivalent
    if (angleDegrees < 0)
        angleDegrees += 360;
    return angleDegrees;
}

inline constexpr double
getAngle(const SDL_FPoint& a, const SDL_FPoint& b) {
    return getAngle(a.x, a.y, b);
}

/**
 * @brief Calculate a new position against a start position with a angle and distance
 * @param start Start position
 * @param angle Angle to be used
 * @param distance Distance from center position
 * @return
 */
constexpr SDL_FPoint
offsetAngle(const SDL_FPoint& start, const double& angle, const float& distance) {
    const auto radians = static_cast<float>(angle * M_PI / 180.0);
    return SDL_FPoint{ start.x + distance * cos(radians), start.y + distance * sin(radians) };
}

inline constexpr double
getAngle(const float& ax, const float& ay, const float& bx, const float& by) {
    return getAngle(SDL_FPoint{ ax, ay }, SDL_FPoint{ bx, by });
}

/**
 * @brief Return the distance between 2 SDL_FPoints (a^2 + b^2 = c^2)
 * @param a Position 1
 * @param b Position 2
 * @return The distance as float. The number indicate the number of squares between
 */
constexpr float
getDistance(const SDL_FPoint& a, const SDL_FPoint& b) {
    // No need to worry about negative values since we square the numbers, removing all negative numbers
    const auto dx = a.x - b.x;
    const auto dy = a.y - b.y;
    return (sqrt(dx * dx + dy * dy)) / 16.0f;
}

}