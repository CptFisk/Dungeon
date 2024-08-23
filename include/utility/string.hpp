#pragma once
#include <cctype>
#include <string>
#include <regex>

namespace Utility {

/**
 * @brief Check if a character is equal to a-Z or A-Z.
 * @param c Character to check
 * @return true
 * @return false
 */
constexpr bool
isCharacter(const char& c) {
    const int v = static_cast<int>(toupper(c));
    return (v >= 65 && v <= 90) ? true : false;
}

/**
 * @brief Check if a character is of type 0-9
 * @param c
 * @return
 */
constexpr bool
isNumber(const char& c) {
    const int v = static_cast<int>(c);
    return (v >= 48 && v <= 57) ? true : false;
}

/**
 * @brief Return the value of a character. Aa = 0, Bb = 1 and so on.
 * @brief If the character is illegal it will return -1
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

/**
 * @brief Check that a string only contains a-z A-Z and space
 * @param s string to be checked
 */
bool
isCharacter(const std::string& s){
    std::regex pattern("^[a-zA-Z ]*$");
    return std::regex_match(s, pattern) ? true : false;
}

/**
 *
 * @param s Check that a string only contains 0-9
 * @param s string to be checked
 */
bool
isNumber(const std::string& s){
    std::regex pattern("^[0-9]*$");
    return std::regex_match(s, pattern) ? true : false;
}
}