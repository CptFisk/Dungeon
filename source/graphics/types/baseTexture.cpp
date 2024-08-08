#include <graphics/types/baseTexture.hpp>

namespace Graphics {
BaseTexture::BaseTexture(SDL_Texture* texture, const int& w, const int& h)
  : Texture(texture, w, h, TextureTypes::BaseTexture){};

BaseTexture::~BaseTexture(){};

}