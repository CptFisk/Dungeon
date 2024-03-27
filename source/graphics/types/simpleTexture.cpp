#include <graphics/types/simpleTexture.hpp>

namespace Graphics {
typeSimpleTexture::typeSimpleTexture()
  : Texture(nullptr)
  , Width(0)
  , Height(0) {}

typeSimpleTexture::typeSimpleTexture(SDL_Texture* texture, const int& w, const int& h)
  : Texture(texture)
  , Width(w)
  , Height(h) {}

std::pair<SDL_Texture*, SDL_FRect>
typeSimpleTexture::operator[](size_t n) const {
    if (n == -1)
        return { Texture, Views[rand() % Views.size()] };
    if (n < Views.size()) {
        return { Texture, Views[n] };
    } else {
        throw std::runtime_error("Index out of bounds");
    }
}

typeSimpleTexture&
typeSimpleTexture::operator=(const Graphics::typeSimpleTexture& other) {
    if (this == &other)
        return *this;
    Texture = other.Texture;
    Views   = other.Views;

    return *this;
}
}