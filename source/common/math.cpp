#include <common/math.hpp>

namespace Common{

int
getIndex(const float& x, const float& y, Level::typeHeader* header){
    return getIndex(static_cast<int>(x), static_cast<int>(y), header);
}

int
getIndex(const std::pair<int, int>& coords, Level::typeHeader* header){
    return getIndex(coords.first, coords.second, header);
}

int
getIndex(const int& x, const int& y, Level::typeHeader* header){
    if (header == nullptr)
        return size_t();
    auto _x     = static_cast<int>(x);
    auto _y     = static_cast<int>(y);
    auto _width = static_cast<int>(header->Level.SizeX);
    return _x + _y * _width;
}

std::pair<int, int>
getClickCoords(const float& x, const float& y, const typeScale& scale){
    auto _x = std::floor(static_cast<float>(x) / (16.0f * scale.ScaleX));
    auto _y = std::floor(static_cast<float>(y) / (16.0f * scale.ScaleY));
    return std::make_pair(_x, _y);
}

}