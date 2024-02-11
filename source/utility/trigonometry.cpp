#include <cmath>
#include <utility/trigonometry.hpp>

namespace Utility {
void
calculateVector(const float& angle, const float& velocity, float& x, float& y) {
    auto angleRadians = angle * M_PI / 180.0;

    auto deltaX = velocity * cos(angleRadians);
    auto deltaY = velocity * sin(angleRadians);
    x           = static_cast<float>(deltaX);
    y           = static_cast<float>(deltaY);
}

float
calculateAngle(const std::pair<float, float>& p1, const std::pair<float, float>& p2) {
    return calculateAngle(p1.first, p1.second, p2.first, p2.second);
}
float
calculateAngle(const float& x1, const float& y1, const float& x2, const float& y2) {
    auto deltaX = x2 - x1;
    auto deltaY = y2 - y1;

    auto angleRadians = atan2(deltaY, deltaX);
    return angleRadians* 180 / M_PI;
}
}