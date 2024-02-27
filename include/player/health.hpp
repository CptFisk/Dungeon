#pragma once
#include <common/scale.hpp>

namespace Player{
class Health{
  public:
    Health(bool& visible, int& health, Common::typeScale& scale);
  protected:
  private:
    bool& mVisible;
    int& mHealth;
    Common::typeScale& mScale;
};
}