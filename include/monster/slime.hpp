#pragma once
#include <monster/monster.hpp>

namespace Monster {
class Slime : public BaseMonster {
  public:
    Slime(const int& health, const float& velocity, SDL_FRect* playerPosition);
    ~Slime();

    BaseMonster* spawn(const float& x, const float& y) const override;
    void interact() override;
  protected:

  private:
    int       mTicks; // Current ticks
    const int IDLE;
    const int MOVE;
};

}