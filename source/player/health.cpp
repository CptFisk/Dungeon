#include <player/health.hpp>

namespace Player {
Health::Health(bool& visible, int& health, Common::typeScale& scale)
  : mVisible(visible)
  , mHealth(health)
  , mScale(scale)
  , mPosition(8.0f * scale.ScaleX, scale.WindowY - (16 * scale.ScaleY), 16.0f * scale.ScaleX, 16.0f * scale.ScaleY) {}

}