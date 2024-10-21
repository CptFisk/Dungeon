#include <graphics/floatingText.hpp>
#include <utility/math.hpp>
namespace Graphics {

FloatingText::FloatingText(SDL_FPoint position, SDL_Texture*& texture, const int& w, const int& h, const double long& duration)
  : pTexture(texture)
  , mDuration(duration)
  , mTicks(0)
  , mPosition{ position.x, position.y, static_cast<float>(w), static_cast<float>(h) } {}

bool
FloatingText::expired() {
    return mTicks++ >= mDuration ? true : false;
}

typeDrawData
FloatingText::getFloatingText() {
    return typeDrawData{ pTexture, nullptr, &mPosition };
}

}