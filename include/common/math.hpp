#pragma once
#include <level/structures.hpp>
#include <utility>
#include <common/scale.hpp>

namespace Common {

// Select an index in map
int
getIndex(const float& x, const float& y, Level::typeHeader* header);
int
getIndex(const std::pair<int, int>& coords, Level::typeHeader* header);
int
getIndex(const int& x, const int& y, Level::typeHeader* header);

// Return the coordinates that you click on
std::pair<int, int>
getClickCoords(const float& x, const float& y, const typeScale& scale);

}