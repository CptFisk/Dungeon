#include <level/tile.hpp>

namespace Level {
Tile::Tile(const float& x, const float& y)
  : mPosition{ x * 16.0f, y * 16.0f, 16.0f, 16.0f } {}

Tile::Tile(const float& x, const float& y, const Common::typeScale& scale)
  : mPosition{ x * 16.0f * scale.ScaleX, y * 16.0f * scale.ScaleY, 16.0f * scale.ScaleX, 16.0f * scale.ScaleY } {}

size_t
Tile::addData(SDL_Texture* texture, const SDL_FRect& viewport) {
    mData.emplace_back(tileData{ texture, viewport });
    return mData.size();
}

}