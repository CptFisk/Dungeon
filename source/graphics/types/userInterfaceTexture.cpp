#include <graphics/types/userInterfaceTexture.hpp>

namespace Graphics {

UserInterfaceTexture::UserInterfaceTexture(SDL_Texture* texture, const int& w, const int& h, const int& top, const int& bottom, const int& left, const int& right)
  : mMarginTop(top)
  , mMarginBottom(bottom)
  , mMarginLeft(left)
  , mMarginRight(right)
  , Texture(texture, w, h, TextureTypes::UserInterface) {}

}