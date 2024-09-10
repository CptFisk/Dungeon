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