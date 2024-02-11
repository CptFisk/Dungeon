#include <utility/calculateVector.hpp>
#include <cmath>

namespace Utility{
void calculateVector(const float& angle, const float& velocity, float &x, float &y){
    auto angleRadians = angle * M_PI / 180.0;

    auto deltaX = velocity * cos(angleRadians);
    auto deltaY = velocity * sin(angleRadians);
    x = static_cast<float>(deltaX);
    y = static_cast<float>(deltaY);
}
}