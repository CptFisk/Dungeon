#include <level/tile.hpp>

namespace Level {

Tile::Tile(const int& x, const int& y)
  : xPos(static_cast<float>(x) * 16.0f)
  , yPos(static_cast<float>(y) * 16.0f) {}

Tile::Tile(const int& x, const int& y, const Common::typeScale& scale)
  : xPos(static_cast<float>(x) * 16.0f * scale.ScaleX)
  , yPos(static_cast<float>(y) * 16.0f * scale.ScaleY) {}

Tile&
Tile::operator=(const Level::Tile& other) {
    if (this == &other)
        return *this;
    data = other.data;
    return *this;
}

void
Tile::clear() {
    data.clear();
}

void
Tile::addData(SDL_Texture* texture, SDL_FRect viewport, const float& w, const float& h) {
    data.emplace_back(texture, viewport, SDL_FRect{ xPos, yPos, w, h });
}

void
Tile::addData(SDL_Texture* texture, SDL_FRect viewport, const float& w, const float& h, const Common::typeScale scale) {
    data.emplace_back(texture, viewport, SDL_FRect{ xPos, yPos, w * scale.ScaleX, h * scale.ScaleY });
}

std::vector<Common::typeDrawData>
Tile::getTile() {
    std::vector<Common::typeDrawData> ret;
    for (auto& tile : data)
        ret.emplace_back(tile.Texture, &tile.Viewport, &tile.Position);
    return ret;
}

}