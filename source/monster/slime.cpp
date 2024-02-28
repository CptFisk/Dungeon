#include <monster/slime.hpp>

namespace Monster{
Slime::Slime(const int& health, const float& velocity) : BaseMonster(health, velocity){}

Slime::~Slime() {}
}