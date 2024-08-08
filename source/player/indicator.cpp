#include <player/indicator.hpp>
#include <utility/math.hpp>

namespace Player {
Indicator::Indicator(bool&                        visible,
                     int&                         value,
                     const float&                 distance,
                     SDL_Renderer*                renderer,
                     Graphics::AnimatedTexture*   texture,
                     const Graphics::BaseTexture& numbers)
  : mVisible(visible)
  , mValue(value)
  , pRenderer(renderer)
  , pIconTexture(texture)
  , mNumbers(numbers)
  , mPositionIcon(8.0f, 192 - distance, 16.0f, 16.0f)
  , mPositionNumber({ 28.0f, (192 - distance) + 4.0f, 8.0f, 8.0f },
                    { 36.0f, (192 - distance) + 4.0f, 8.0f, 8.0f },
                    { 44.0f, (192 - distance) + 4.0f, 8.0f, 8.0f }) {}

void
Indicator::draw() {
    if (mVisible) {
        // Icon
        SDL_RenderCopyF(pRenderer, pIconTexture->getTexture(), pIconTexture->getViewport(), &mPositionIcon);
        // Numbers
        int pos = 0;
        if (mValue > 0 && mValue < 999) {
            for (const auto& n : Utility::splitNumbers(mValue))
                SDL_RenderCopyF(pRenderer, mNumbers.getTexture(), &mNumbers.getViewport(n), &mPositionNumber[pos++]);
        }
    }
}
}