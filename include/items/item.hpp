#pragma once
#include <cstdint>
#include <graphics/types/drawData.hpp>
#include <graphics/types/texture.hpp>
#include <items/slots.hpp>
#include <stats/stats.hpp>
#include <string>
namespace Items {

class Item {
  public:
    Item(Graphics::Texture* texture, const SlotType& slot, const std::string& desc, const int16_t& id, const Stats::Stats& stats);
    /**
     * @return Return the graphics linked to the items
     */
    virtual ~Item() = default;
    SDL_Texture* getTexture();
    /**
     * @return Return the slot the item belongs to
     */
    [[nodiscard]] SlotType getSlotType() const;
    /**
     * @return Return the stats linked to the item
     */
    [[nodiscard]] Stats::Stats getStats() const;
    /**
     * @return The item Id (should always be unique)
     */
    [[nodiscard]] int16_t getId() const;

  protected:
  private:
    Graphics::Texture* mTexture; // Reference to the texture, can be everything as long as it fits the dimensions
    const SlotType     mSlot;    // Slot that its bound to
    const int16_t      mId;      // Item id, should be unique
    const Stats::Stats mStats;
    const std::string  mDescription; // Item description
};

}