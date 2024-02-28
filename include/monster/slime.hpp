#pragma once
#include <monster/monster.hpp>

namespace Monster {
class Slime : public BaseMonster {
  public:
    Slime(const int& health, const float& velocity, SDL_FRect* playerPosition);
    ~Slime();

    BaseMonster* spawn(const float& x, const float& y) const override;

    void move(Directions direction) override;

  protected:
  private:
};

}