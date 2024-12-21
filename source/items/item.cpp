#include <items/item.hpp>

namespace Items {

Item::Item(Graphics::Texture* texture, const Items::SlotType& slot, const int16_t& id, const Stats::Stats stats)
  : mTexture(texture)
  , mSlot(slot)
  , mId(id)
  , mStats(stats) {}

SDL_Texture*
Item::getTexture() {
    return mTexture->getTexture();
}

SlotType
Item::getSlotType() const {
    return mSlot;
}

}