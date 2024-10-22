#include <graphics/floatingText.hpp>
#include <utility/math.hpp>
namespace Graphics {

FloatingTexture::FloatingTexture(SDL_FPoint position, SDL_Texture*& texture, const int& w, const int& h, const double long& duration)
  : pTexture(texture)
  , mDuration(duration)
  , mTicks(0)
  , mPosition{ position.x, position.y, static_cast<float>(w), static_cast<float>(h) } {}

bool
FloatingTexture::expired() {
    return mTicks++ >= mDuration ? true : false;
}

typeDrawData
FloatingTexture::getFloatingText() {
    return typeDrawData{ pTexture, nullptr, &mPosition };
}

}