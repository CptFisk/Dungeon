#include <player/indicator.hpp>
#include <utility/math.hpp>

namespace Player {
Indicator::Indicator(bool&                              visible,
                     int&                               value,
                     const float&                       distance,
                     SDL_Renderer*                      renderer,
                     Common::typeScale&                 scale,
                     Graphics::AnimatedTexture*         texture,
                     const Graphics::typeSimpleTexture& numbers)
  : mVisible(visible)
  , mValue(value)
  , mScale(scale)
  , pRenderer(renderer)
  , pIconTexture(texture)
  , mNumbers(numbers)
  , mPositionIcon(8.0f * scale.ScaleX,
                  static_cast<float>(scale.WindowY) - (distance * scale.ScaleY),
                  8.0f * scale.ScaleX,
                  8.0f * scale.ScaleY)
  , mPositionNumber(
      { 20.0f * scale.ScaleX, static_cast<float>(scale.WindowY) - (distance * scale.ScaleY), 8.0f * scale.ScaleX, 8.0f * scale.ScaleY },
      { 28.0f * scale.ScaleX, static_cast<float>(scale.WindowY) - (distance * scale.ScaleY), 8.0f * scale.ScaleX, 8.0f * scale.ScaleY },
      { 36.0f * scale.ScaleX, static_cast<float>(scale.WindowY) - (distance * scale.ScaleY), 8.0f * scale.ScaleX, 8.0f * scale.ScaleY }) {}

void
Indicator::draw() {
    if (mVisible) {
        // Icon
        SDL_RenderTexture(pRenderer, pIconTexture->getTexture(), pIconTexture->getViewport(), &mPositionIcon);
        // Numbers
        int pos = 0;
        if (mValue > 0 && mValue < 999) {
            for (const auto& n : Utility::splitNumbers(mValue))
                SDL_RenderTexture(pRenderer, mNumbers.Texture, &mNumbers.Views[n], &mPositionNumber[pos++]);
        }
    }
}
}