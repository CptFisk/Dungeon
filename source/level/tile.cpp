#include <level/tile.hpp>

namespace Level {

Tile::Tile(const int& x, const int& y)
  : position{ static_cast<float>(x) * 16.0f, static_cast<float>(y) * 16.0f, 16.0f, 16.0f } {}

Tile::Tile(const int& x, const int& y, const Common::typeScale& scale)
  : position{ static_cast<float>(x) * 16.0f * scale.ScaleX, static_cast<float>(y) * 16.0f * scale.ScaleY, 16.0f * scale.ScaleX, 16.0f * scale.ScaleY } {}

void
Tile::clear() {
    data.clear();
}

size_t
Tile::addData(SDL_Texture* texture, const SDL_FRect& viewport) {
    data.emplace_back(tileData{ texture, viewport });
    return data.size();
}

std::vector<Common::typeDrawData>
Tile::getTile() {
    std::vector<Common::typeDrawData> retVal;
    for(auto& element : data)
        retVal.emplace_back(Common::typeDrawData{element.Texture, &element.Viewport, &position});
    return retVal;
}

}