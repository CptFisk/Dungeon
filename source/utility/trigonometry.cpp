#include <cmath>
#include <utility/trigonometry.hpp>

namespace Utility {

float
calculateAngle(const std::pair<float, float>& p1, const std::pair<float, float>& p2) {
    return calculateAngle(p1.first, p1.second, p2.first, p2.second);
}
float
calculateAngle(const float& x1, const float& y1, const float& x2, const float& y2) {
    auto deltaX = x2 - x1;
    auto deltaY = y2 - y1;

    auto angleRadians = atan2(deltaY, deltaX);
    auto angleDegrees = angleRadians * 180 / M_PI;

    // Convert negative angles to positive equivalent
    if (angleDegrees < 0)
        angleDegrees += 360;

    return angleDegrees;
}
}