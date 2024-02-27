#include <player/health.hpp>

namespace Player {
Health::Health(bool& visible, int& health, SDL_Renderer* renderer, Common::typeScale& scale, Graphics::AnimatedTexture* texture)
  : mVisible(visible)
  , mHealth(health)
  , mScale(scale)
  , pRenderer(renderer)
  , mPosition(8.0f * scale.ScaleX, static_cast<float>(scale.WindowY) - (32.0f * scale.ScaleY), 16.0f * scale.ScaleX, 16.0f * scale.ScaleY)
  , pHeartTexture(texture) {}

void
Health::draw() {
    if (mVisible)
        SDL_RenderTexture(pRenderer, pHeartTexture->getTexture(), pHeartTexture->getViewport(), &mPosition);
}
}