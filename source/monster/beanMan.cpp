#include <iostream>
#include <monster/beanMan.hpp>

namespace Monster {
BeanMan::BeanMan(const float&                                                            width,
                 const float&                                                            height,
                 const int&                                                              health,
                 const float&                                                            velocity,
                 const std::string& name,
                 const std::optional<std::unordered_map<std::string, std::any>>& defaults)
  : mMonsterWidth(width)
  , mMonsterHeight(height)
  , BaseMonster(health, velocity, name, defaults) {}

BeanMan::~BeanMan() = default;

void
BeanMan::attack(){

}

BaseMonster*
BeanMan::spawn(const float& x, const float& y) const {
    const auto xPos         = x * 16.0f; // One square is 16 pixels
    const auto yPos         = y * 16.0f; // One square is 16 pixels
    auto       obj          = new BeanMan(*this);
    obj->mMonsterPosition.x = xPos + FLOAT((16 - mMonsterWidth) / 2);
    obj->mMonsterPosition.y = yPos + FLOAT((16 - mMonsterHeight) / 2);
    obj->mMonsterPosition.w = mMonsterWidth;
    obj->mMonsterPosition.h = mMonsterHeight;
    obj->mMonsterCenter.x   = xPos + (mMonsterWidth / 2.0f);
    obj->mMonsterCenter.y   = yPos + (mMonsterHeight / 2.0f);
    obj->luaFile = this->luaFile;
    obj->mRetains           = mRetains;
    return obj;
}

}