#include <graphics/types/fontTexture.hpp>

namespace Graphics {
FontTexture::FontTexture(SDL_Texture* texture, SDL_Renderer*& renderer, const int& w, const int& h)
  : pRenderer(renderer)
  , Texture(texture, w, h, TextureTypes::BaseTexture) {};

FontTexture::~FontTexture(){};

}