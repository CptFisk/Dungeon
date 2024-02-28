#pragma once

namespace Monster{
class BaseMonster{
  public:
    BaseMonster(const int& health, const float& velocity);
    ~BaseMonster();
    bool damage(const int& damage);
  protected:
  private:
    const float mVelocity;
    int mHealth;    //Monster health
};
}