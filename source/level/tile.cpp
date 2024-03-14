#include <level/tile.hpp>

namespace Level {
Tile::Tile(const float& x, const float& y)
  : position{ x * 16.0f, y * 16.0f, 16.0f, 16.0f } {}

Tile::Tile(const float& x, const float& y, const Common::typeScale& scale)
  : position{ x * 16.0f * scale.ScaleX, y * 16.0f * scale.ScaleY, 16.0f * scale.ScaleX, 16.0f * scale.ScaleY } {}

void
Tile::clear() {
    data.clear();
}

size_t
Tile::addData(SDL_Texture* texture, const SDL_FRect& viewport) {
    data.emplace_back(tileData{ texture, viewport });
    return data.size();
}

}