#pragma once
#include <array>
#include <common/scale.hpp>
#include <graphics/types/drawData.hpp>
#include <graphics/types/userInterfaceTexture.hpp>
#include <items/item.hpp>
#include <items/slot.hpp>
#include <items/slots.hpp>
#include <items/weaponType.hpp>
namespace Items {

class Inventory {
  public:
    Inventory();
    ~Inventory() = default;

    [[nodiscard]] std::array<Slot, 30>& getSlots();
    /**
     * @brief Using the mouse to click on a specific square.
     * @return True if graphics should be re-calculated
     */
    [[nodiscard]] bool selectItem(const uint8_t& index, bool& selectorVisible);
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
    /**
     * @brief Swap the position of 2 items in the inventory
     * @param enabled Swapping is enabled
     * @param index1 Index of first item
     * @param index2 Index of second item
     * @return True is swapping was successful
     */
    bool       swap(const bool& enabled, const int& index1, const int& index2);
    WeaponType getWeapon(const int& index);
    /**
     * @return Return the slot number that can be used in @ref mSlots
     */
    static int getSlotId(const SlotType& slot);

  private:
    uint8_t              mSelected;
    std::array<Slot, 30> mSlots;
    Stats::Stats         mItemStats; // Hold the attribute points for all items the player is carrying
};
}