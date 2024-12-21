#include <items/item.hpp>

namespace Items {

Item::Item(Graphics::Texture* texture, const Items::SlotType& slot, const int16_t& id)
  : mTexture(texture)
  , mSlot(slot)
  , mId(id) {}

SDL_Texture*
Item::getTexture() {
    return mTexture->getTexture();
}

SlotType
Item::getSlotType() const {
    return mSlot;
}

}