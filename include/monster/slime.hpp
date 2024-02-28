#pragma once
#include <monster/monster.hpp>

namespace Monster {
class Slime : public BaseMonster {
  public:
    Slime(const int& health, const float& velocity);
    ~Slime();

    BaseMonster * spawn() const override{
        return new Slime(*this);
    }

    void move(Directions direction) override {
        mMonsterPosition.x += 2.0f;
        mMonsterPosition.y += 2.0f;
    }

  protected:
  private:
};

}