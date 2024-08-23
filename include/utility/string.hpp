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

constexpr bool
isNumber(const char& c) {
    const int v = static_cast<int>(c);
    return (c >= 48 && c <= 57) ? true : false;
}

/**
 * @brief Return the value of a character. Aa = 0, Bb = 1 and so on.
 * @brief If the character is illegal it will return -1
 *
 * @param c Character
 * @return constexpr int
 */
constexpr int
charValue(const char& c) {
    if (!isCharacter(c))
        return -1;
    const int v = static_cast<int>(toupper(c)) - 65;
    return v;
}
}