#include <common/sdl.hpp>
#include <editor/visualTile.hpp>

namespace Editor {
VisualTile::VisualTile(const int& x, const int& y, Graphics::typeSimpleTexture number, const Common::typeScale& scale)
  : texture(nullptr)
  , position(Common::newSDL_FRectScaled(x, y, scale))
  , counter(0)
  , numbers(std::move(number)) {}

void
VisualTile::newOverlay(SDL_Texture* overlay) {
    texture = overlay;
}

SDL_Texture *
VisualTile::getOverlay() {
    return texture;
}

SDL_FRect&
VisualTile::getPosition(){
    return position;
}

void
VisualTile::incrementCounter() {
    counter++;
}

void
VisualTile::resetCounter() {
    counter = 0;
}

std::pair<SDL_Texture*, SDL_Rect>
VisualTile::getNumber() {
    return { numbers.Texture, numbers.getView(counter) };
}
}