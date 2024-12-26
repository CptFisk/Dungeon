#pragma once
#include <items/item.hpp>
#include <items/weaponType.hpp>

namespace Items {

class Weapon : public Item {
  public:
    Weapon(Graphics::Texture*  texture,
           const SlotType&     slot,
           const WeaponType&    type,
           const std::string&  desc,
           const int16_t&      id,
           const Stats::Stats& stats);
    ~Weapon();
    WeaponType getWeaponType() const;

  protected:
  private:
    const WeaponType mType;
};

}