#pragma once
#include <cstdint>
#include <graphics/types/drawData.hpp>
#include <graphics/types/texture.hpp>
#include <items/slots.hpp>

namespace Items {

class Item {
  public:
    Item(Graphics::Texture* texture, const SlotType& slot, const int16_t& id);
    /**
     * @return Return the graphics linked to the items
     */
    SDL_Texture*           getTexture();
    /**
     * @return Return the slot the item belongs to
     */
    [[nodiscard]] SlotType getSlotType() const;

  protected:
  private:
    Graphics::Texture* mTexture; // Reference to the texture, can be everything as long as it fits the dimensions
    const SlotType     mSlot;    // Slot that its bound to
    const int16_t      mId;      // Item id, should be unique
};

}