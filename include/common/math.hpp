#pragma once
#include <common/scale.hpp>
#include <error.hpp>
#include <file/editorFile.hpp>
#include <optional>
#include <utility>

namespace Common {

// Select an index in map
std::optional<int>
getIndex(const float& x, const float& y, const float& maxX);
std::optional<int>
getIndex(const std::pair<int, int>& coords, const int& maxX);
std::optional<int>
getIndex(const int& x, const int& y, const int& maxX);

// Return the coordinates that you click on
constexpr std::pair<int, int>
getClickCoords(const float& x, const float& y, const typeScale& scale){
    const auto _x = std::floor(static_cast<float>(x) / (16.0f * scale.selectedScale));
    const auto _y = std::floor(static_cast<float>(y) / (16.0f * scale.selectedScale));
    return std::make_pair(_x, _y);
}

/**
 * @brief Return coordinates based index position.
 * @brief Example: A 4x4 grid exist and you give position 5.
 * @brief That correlate to the position x = 0, y =1.
 * @param pos
 * @return
 */
constexpr std::pair<int,int>
getCoords(const int& pos, const int& width, const int& height){
    ASSERT_WITH_MESSAGE(pos > width * height || width == 0 || height == 0, "Invalid values")
    const int x = pos % width;
    const int y = pos / width;
    return std::make_pair(x, y);
}

int findLcm(const std::vector<int>& values);
int lcm(const int& a, const int &b);
}