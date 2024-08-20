#include <graphics/types/userInterfaceTexture.hpp>

namespace Graphics {

UserInterfaceTexture::UserInterfaceTexture(SDL_Texture* texture, const int& w, const int& h, const int& top, const int& bottom, const int& left, const int& right)
  : mMarginTop(top)
  , mMarginBottom(bottom)
  , mMarginLeft(left)
  , mMarginRight(right)
  , Texture(texture, w, h, TextureTypes::UserInterface) {}

int
UserInterfaceTexture::getMarginTop() const {
    return mMarginTop;
}

float
UserInterfaceTexture::getMarginTopF() const {
    return static_cast<float>(mMarginTop);
}

int
UserInterfaceTexture::getMarginBottom() const {
    return mMarginBottom + mHeight;
}

float
UserInterfaceTexture::getMarginBottomF() const {
    return static_cast<float>(mMarginBottom + mHeight);
}

int
UserInterfaceTexture::getMarginLeft() const {
    return mMarginLeft;
}

float
UserInterfaceTexture::getMarginLeftF() const {
    return static_cast<float>(mMarginLeft);
}

int
UserInterfaceTexture::getMarginRight() const {
    return mMarginRight + mWidth;
}

float
UserInterfaceTexture::getMarginRightF() const {
    return static_cast<float>(mMarginRight  + mWidth);
}
}