#pragma once
#include <SDL.h>
#include <algorithm>
#include <vector>

namespace Utility {
/**
 * @brief Split a number into a vector.
 * @param n Number to be split
 * @return Vector with the same size as numbers of digits
 * @example splitNumbers(123) will return a vector<int>{1,2,3}
 */
std::vector<int>
splitNumbers(int n);

template<typename T>
bool
allEqual(T value) {
    return true;
}

template<typename T, typename... Args>
bool
allEqual(T first, Args... args) {
    return ((first == args) && ...);
}

template<typename T>
bool
isAnyEqualTo(T value, T compareValue) {
    return value == compareValue;
}

template<typename T, typename... Args>
bool
isAnyEqualTo(T first, T compareValue, Args... args) {
    return (first == compareValue) || isAnyEqualTo(args..., compareValue);
}

}