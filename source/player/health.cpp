#include <player/health.hpp>

namespace Player {
Health::Health(bool& visible, int& health, Common::typeScale& scale)
  : mVisible(visible)
  , mHealth(health)
  , mScale(scale) {}

}