#include <items/weapon.hpp>

namespace Items {
Weapon::Weapon(Graphics::Texture*     texture,
               const Items::SlotType& slot,
               const WeaponType&       type,
               const std::string&     desc,
               const int16_t&         id,
               const Stats::Stats&    stats)
  : mType(type)
  , Item(texture, slot, desc, id, stats) {}
}