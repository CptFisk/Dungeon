#include <level/tile.hpp>

namespace Level {

#ifdef GAME_MODE
Tile::Tile(const int& x, const int& y)
  : xPos(static_cast<float>(x) * 16.0f)
  , yPos(static_cast<float>(y) * 16.0f) {}
#endif

#ifdef EDITOR_MODE
Tile::Tile(const int& x, const int& y, const Common::typeScale& scale)
  : xPos(static_cast<float>(x) * 16.0f * scale.factorX)
  , yPos(static_cast<float>(y) * 16.0f * scale.factorY) {}
#endif
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

#ifdef GAME_MODE
void Tile::addData(SDL_Texture* texture, SDL_FRect viewport, const int& w, const int& h){
    addData(texture, viewport, static_cast<float>(w), static_cast<float>(h));
}

void
Tile::addData(SDL_Texture* texture, SDL_FRect viewport, const float& w, const float& h) {
    data.emplace_back(texture, viewport, SDL_FRect{ xPos, yPos, w, h });
}
#endif

#ifdef EDITOR_MODE
void
Tile::addData(SDL_Texture* texture, SDL_FRect viewport, const float& w, const float& h, const Common::typeScale scale) {
    data.emplace_back(texture, viewport, SDL_FRect{ xPos, yPos, w * scale.factorX, h * scale.factorY });
}
#endif

std::vector<Common::typeDrawData>
Tile::getTile() {
    std::vector<Common::typeDrawData> ret;
    for (auto& tile : data)
        ret.emplace_back(tile.Texture, &tile.Viewport, &tile.Position);
    return ret;
}

}