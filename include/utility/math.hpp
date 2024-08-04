#pragma once
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
}