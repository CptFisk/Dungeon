#include <graphics/floatingText.hpp>
#include <utility/math.hpp>
namespace Graphics {

FloatingTexture::FloatingTexture(SDL_FRect& position, SDL_Rect* viewport, SDL_Texture*& texture, const double long& duration)
  : pTexture(texture)
  , pViewport(viewport)
  , mDuration(duration)
  , mTicks(0)
  , mPosition(position) {}

bool
FloatingTexture::expired() {
    return mTicks++ >= mDuration ? true : false;
}

typeDrawData
FloatingTexture::getFloatingText() {
    return typeDrawData{ pTexture, pViewport, &mPosition };
}

}