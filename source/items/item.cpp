#include <items/item.hpp>

namespace Items {

Item::Item(Graphics::Texture* texture, const Items::SlotType& slot, const std::string& desc, const int16_t& id, const Stats::Stats& stats)
  : mTexture(texture)
  , mSlot(slot)
  , mDescription(desc)
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

Stats::Stats
Item::getStats() const {
    return mStats;
}

int16_t
Item::getId() const {
    return mId;
}

}