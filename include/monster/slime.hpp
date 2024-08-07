#pragma once
#include <monster/monster.hpp>

namespace Monster {
/**
 * @brief Base class for all small slimes that exist.
 */
class Slime : public BaseMonster {
  public:
    Slime(const int&                                                         health,
          const float&                                                       velocity,
          const float&                                                         radius,
          SDL_FPoint&                                                        playerCenter,
          std::function<bool(const SDL_FPoint&, const float&, const float&)> checkWalls);
    ~Slime();

    [[nodiscard]] BaseMonster* spawn(const float& x, const float& y) const override;
    void                       interact() override;

  protected:
  private:
    const float MONSTER_WIDTH  = 12.0f;
    const float MONSTER_HEIGHT = 10.0f;
    const float   mRadius; // How close the player needs to be to trigger monster
};

}