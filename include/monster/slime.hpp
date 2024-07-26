#pragma once
#include <monster/monster.hpp>

namespace Monster {
class Slime : public BaseMonster {
  public:
    Slime(const int&                                                            health,
          const float&                                                          velocity,
          SDL_FPoint&                                                           playerCenter,
          std::function<bool(const SDL_FPoint&, const int&, const Directions&)> checkWalls);
    ~Slime();

    [[nodiscard]] BaseMonster* spawn(const float& x, const float& y) const override;
    void                       interact() override;

  protected:
  private:
    const float SLIME_WIDTH  = 8.0f;
    const float SLIME_HEIGHT = 8.0f;
    int         mTicks; // Current ticks
    const int   IDLE;
    const int   MOVE;
};

}