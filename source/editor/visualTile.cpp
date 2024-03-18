#include <common/sdl.hpp>
#include <editor/visualTile.hpp>
namespace Editor {
VisualTile::VisualTile(const int& x, const int& y, Graphics::typeSimpleTexture number, const Common::typeScale& scale)
  : texture(nullptr)
  , position(Common::newSDL_FRectScaled(x, y, scale))
  , numbers(number) {}

void
VisualTile::newOverlay(SDL_Texture* overlay) {
    texture = overlay;
}

std::pair<SDL_Texture*, SDL_FRect>
VisualTile::getOverlay() {
    return { texture, position };
}

void
VisualTile::incrementCounter() {
    counter++;
}

void
VisualTile::resetCounter() {
    counter = 0;
}

std::pair<SDL_Texture*, SDL_FRect>
VisualTile::getNumber() {
    return { numbers.Texture, numbers.Views[counter] };
}
}