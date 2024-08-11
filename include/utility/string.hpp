#pragma once
#include <cctype>
#include <string>


namespace Utility {

/**
 * @brief Check if a character is equal to a-Z or A-Z.
 *
 * @param c Character to check
 * @return true
 * @return false
 */
constexpr bool
isCharacter(const char& c) {
    const int v = static_cast<int>(toupper(c));
    return (v >= 65 && v <= 90) ? true : false;
}
}