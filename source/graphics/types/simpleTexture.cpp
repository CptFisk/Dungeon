#include <graphics/types/simpleTexture.hpp>

namespace Graphics {
SimpleTexture::SimpleTexture(SDL_Texture* texture, const int& w, const int& h)
  : Texture(texture, w, h, TextureTypes::BaseTexture){};

SimpleTexture::~SimpleTexture(){};

}