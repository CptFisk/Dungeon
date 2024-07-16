#pragma once

namespace Utility {
template<typename T>
constexpr T Scale(const T& value, const T& inMin, const T& inMax, const T& outMin, const T& outMax) {
    // Ensure the input value is within the original range
    if (value < inMin)
        return outMin;
    if (value > inMax)
        return outMax;

    // Perform the scaling
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
}