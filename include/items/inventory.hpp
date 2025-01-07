#pragma once
#include <array>
#include <common/scale.hpp>
#include <graphics/types/drawData.hpp>
#include <graphics/types/userInterfaceTexture.hpp>
#include <items/item.hpp>
#include <items/slots.hpp>
#include <items/slot.hpp>
#include <items/weaponType.hpp>
namespace Items {

class Inventory {
  public:
    Inventory(Common::typeScale&              scale,
              Graphics::UserInterfaceTexture* inventory,
              Graphics::UserInterfaceTexture* selector,
              Graphics::Texture*&             userinterface);
    ~Inventory();
    /**
     * @return Return all the draw data related to inventory
     */
    std::vector<Graphics::typeDrawData> getInventory();
    /**
     * @brief Using the mouse to click on a specific square.
     * @param x
     * @param y
     */
    void selectItemMouse(const SDL_FPoint& point);
    /**
     *@brief Add a item to the inventory, it will by default be stored in the first available slot
     */
    void addItem(Item*& item);
    /**
     * @brief Try to equip a item in the correct slot
     * @param itemId
     * @return True if item was found and equipped
     */
    bool equipItem(const uint16_t& itemId);
    /**
     * @brief Calculate all the extra attribute-points earned by items
     */
    void calculateStats();
    /**
     * @return Return the extra stats of all items carried by the player
     */
    [[nodiscard]] Stats::Stats& getItemStats();
    /**
     * @return Return the left hand weapon type
     */
    [[nodiscard]] WeaponType getLeftWeapon();
    /**
     * @return Return the right hand weapon type
     */
    [[nodiscard]] WeaponType getRightWeapon();

  protected:

    bool       swap(const bool& enabled, const int& index1, const int& index2); // Swap 2 items in the inventory
    WeaponType getWeapon(const int& index);
    /**
     * @return Return the slot number that can be used in @ref mSlots
     */
    static int getSlotId(const SlotType& slot);

  private:
    SDL_FPoint           mTopLeft; // Top left coordinate of inventory, used to calculate offsets
    uint8_t              mSelected;
    bool                 mSelectorVisible;
    std::array<Slot, 30> mItems;
    // Graphics
    Graphics::UserInterfaceTexture* pInventory;
    Graphics::UserInterfaceTexture* pSelector;
    // Draw data
    Graphics::typeDrawData mInventoryDrawData;
    Graphics::typeDrawData mSelectorDrawData;
    // Positions
    std::array<SDL_FRect, 30>        mSlotPosition;        // Positions based on resolution
    Common::typeScale                mScale;
    Graphics::Texture*&              pUserInterface; // A reference to the userinterface icon.

    Stats::Stats mItemStats; // Hold the attribute points for all items the player is carrying
};
}