#include <common/math.hpp>

namespace Common{

std::optional<int>
getIndex(const float& x, const float& y, const float& maxX){
    return getIndex(static_cast<int>(x), static_cast<int>(y), static_cast<int>(maxX));
}

std::optional<int>
getIndex(const std::pair<int, int>& coords, const int& maxX){
    return getIndex(coords.first, coords.second, maxX);
}

std::optional<int>
getIndex(const int& x, const int& y, const int& maxX){
    if (maxX == 0)
        return std::nullopt;
    auto _x     = static_cast<int>(x);
    auto _y     = static_cast<int>(y);
    auto _width = static_cast<int>(maxX);
    return _x + _y * _width;
}

std::pair<int, int>
getClickCoords(const float& x, const float& y, const typeScale& scale){
    auto _x = std::floor(static_cast<float>(x) / (16.0f * scale.factorX));
    auto _y = std::floor(static_cast<float>(y) / (16.0f * scale.factorY));
    return std::make_pair(_x, _y);
}

}