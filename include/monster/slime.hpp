#pragma once
#include <monster/monster.hpp>

namespace Monster{
class Slime: public BaseMonster{
  public:
    Slime(const int& health, const float& velocity);
    ~Slime();
  protected:
  private:
};

}