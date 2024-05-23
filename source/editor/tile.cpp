#include <editor/tile.hpp>

namespace Editor {

Tile::Tile(const int& x, const int& y, const Common::typeScale& scale)
  : xPos(static_cast<float>(x) * 16.0f * scale.factorX)
  , yPos(static_cast<float>(y) * 16.0f * scale.factorY) {}

Tile&
Tile::operator=(const Editor::Tile& other) {
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
Tile::addData(SDL_Texture* texture, SDL_Rect viewport, const float& w, const float& h, const Common::typeScale& scale) {
    data.emplace_back(texture, viewport, SDL_FRect{ xPos, yPos, w * scale.factorX, h * scale.factorY });
}


std::vector<Common::typeDrawData>
Tile::getDrawData() {
    std::vector<Common::typeDrawData> ret;
    for (auto& tile : data)
        ret.emplace_back(tile.Texture, &tile.Viewport, &tile.Position);
    return ret;
}

std::vector<tileData>&
Tile::getTileData() {
    return data;
}

}