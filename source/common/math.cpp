#include <common/math.hpp>

namespace Common {

std::optional<int>
getIndex(const float& x, const float& y, const float& maxX) {
    return getIndex(static_cast<int>(x), static_cast<int>(y), static_cast<int>(maxX));
}

std::optional<int>
getIndex(const std::pair<int, int>& coords, const int& maxX) {
    return getIndex(coords.first, coords.second, maxX);
}

std::optional<int>
getIndex(const int& x, const int& y, const int& maxX) {
    if (maxX == 0 || x < 0 || y < 0)
        return std::nullopt;
    auto _x     = static_cast<int>(x);
    auto _y     = static_cast<int>(y);
    auto _width = static_cast<int>(maxX);
    return _x + _y * _width;
}

std::pair<int, int>
getClickCoords(const float& x, const float& y, const typeScale& scale) {
    auto _x = std::floor(static_cast<float>(x) / (16.0f * scale.factorX));
    auto _y = std::floor(static_cast<float>(y) / (16.0f * scale.factorY));
    return std::make_pair(_x, _y);
}

std::optional<std::pair<int, int>>
getCoords(const int& pos, const int& width, const int& height) {
    if (pos > width * height || width == 0 || height == 0)
        return std::nullopt;
    const int x = pos % width;
    const int y = pos / width;
    return std::make_pair(x, y);
}

int findLcm(const std::vector<int>& values){
    if(values.empty())
        return 0;
    int result = values[0];
    for(const auto& value : values){
        result = lcm(result, value);
    }
    return result;
}

int lcm(const int& a, const int& b){
    return (a / std::gcd(a,b)) * b;
}
}