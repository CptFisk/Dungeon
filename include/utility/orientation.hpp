#pragma once
#include <cmath>
#include <global.hpp>

namespace Utility {

constexpr Orientation
getOrientation(double angle) {
    const auto a = static_cast<double>(std::fmod(angle, 360.0));
    if (a <= 45.0 || a > 315.0)
        return East;
    else if (a > 45 && a <= 135)
        return South;
    else if (a > 135 && a <= 225)
        return West;
    else
        return North;
}

}