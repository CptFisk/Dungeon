#include <level/tile.hpp>

namespace Level {
Tile::Tile(const float& x, const float& y)
  : mPosition{ x, y, 1.0f, 1.0f } {}

Tile::Tile(const float& x, const float& y, const Common::typeScale& scale)
  : mPosition{ x, y, 1.0f, 1.0f } {}

size_t
Tile::addData(SDL_Texture* texture, const SDL_FRect& viewport) {
    mData.emplace_back(tileData{ texture, viewport });
    return mData.size();
}

}