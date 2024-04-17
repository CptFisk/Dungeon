#pragma once
#include <common/scale.hpp>
#include <level/file.hpp>
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
std::pair<int, int>
getClickCoords(const float& x, const float& y, const typeScale& scale);

/**
 * @brief Return coordinates based index position.
 * @brief Example: A 4x4 grid exist and you give position 5.
 * @brief That correlate to the position x = 0, y =1.
 * @param pos
 * @return
 */
std::optional<std::pair<int,int>>
getCoords(const int& pos, const int& width, const int& height);

}