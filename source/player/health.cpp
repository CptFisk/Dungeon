#include <player/health.hpp>
#include <utility/math.hpp>

namespace Player {
Health::Health(bool&                              visible,
               int&                               health,
               SDL_Renderer*                      renderer,
               Common::typeScale&                 scale,
               Graphics::AnimatedTexture*         texture,
               const Graphics::typeSimpleTexture& numbers)
  : mVisible(visible)
  , mHealth(health)
  , mScale(scale)
  , pRenderer(renderer)
  , pHeartTexture(texture)
  , mNumbers(numbers)
  , mPositionHeart(8.0f * scale.ScaleX,
                   static_cast<float>(scale.WindowY) - (32.0f * scale.ScaleY),
                   8.0f * scale.ScaleX,
                   8.0f * scale.ScaleY)
  , mPositionNumber(
      { 20.0f * scale.ScaleX, static_cast<float>(scale.WindowY) - (32.0f * scale.ScaleY), 8.0f * scale.ScaleX, 8.0f * scale.ScaleY },
      { 28.0f * scale.ScaleX, static_cast<float>(scale.WindowY) - (32.0f * scale.ScaleY), 8.0f * scale.ScaleX, 8.0f * scale.ScaleY },
      { 36.0f * scale.ScaleX, static_cast<float>(scale.WindowY) - (32.0f * scale.ScaleY), 8.0f * scale.ScaleX, 8.0f * scale.ScaleY }) {}

void
Health::draw() {
    if (mVisible) {
        // Icon
        SDL_RenderTexture(pRenderer, pHeartTexture->getTexture(), pHeartTexture->getViewport(), &mPositionHeart);
        // Numbers
        int pos = 0;
        if (mHealth > 0 && mHealth < 999) {
            for(const auto& n : Utility::splitNumbers(mHealth))
                SDL_RenderTexture(pRenderer, mNumbers.Texture, &mNumbers.Views[n], &mPositionNumber[pos++]);
        }
    }
}
}