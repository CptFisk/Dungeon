#include <graphics/types/generatedTexture.hpp>

namespace Graphics {
GeneratedTexture::GeneratedTexture(SDL_Texture* texture, const int& w, const int& h)
  : Texture(texture, w, h, TextureTypes::GeneratedTexture) {
    SDL_Rect viewport = { 0, 0, w, h }; // This only contains one viewport
    addViewport(viewport);
};

GeneratedTexture::~GeneratedTexture(){};

}