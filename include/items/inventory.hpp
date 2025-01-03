#pragma once
#include <array>
#include <common/scale.hpp>
#include <graphics/types/drawData.hpp>
#include <graphics/types/userInterfaceTexture.hpp>
#include <items/item.hpp>
#include <items/slots.hpp>
#include <items/weaponType.hpp>
namespace Items {

class Inventory {

    struct Slot {
        const SlotType Type; // Item type
        Item*          Item; // Pointer to item
        explicit Slot(const SlotType type)
          : Type(type)
          , Item(nullptr) {}
    };

  public:
    Inventory(Common::typeScale&              scale,
              Graphics::UserInterfaceTexture* inventory,
              Graphics::UserInterfaceTexture* selector,
              Graphics::Texture*&             userinterface);
    ~Inventory();

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
     * @return Return the extra stats of all items carried by the player
     */
    Stats::Stats getStats();
    /**
     * @return Return the left hand weapon type
     */
    WeaponType getLeftWeapon();
    /**
     * @return Return the right hand weapon type
     */
    WeaponType getRightWeapon();

  protected:
    void       calculatePositions();                                            // Used to calulcate positions for all graphical elements
    bool       swap(const bool& enabled, const int& index1, const int& index2); // Swap 2 items in the inventory
    WeaponType getWeapon(const int& index);

  private:
    SDL_FPoint           mTopLeft; // Top left coordinate of inventory, used to calculate offsets
    uint8_t              mSelected;
    bool                 mSelectorVisible;
    std::array<Slot, 30> mSlots;
    // Graphics
    Graphics::UserInterfaceTexture* mInventory;
    Graphics::UserInterfaceTexture* mSelector;
    // Draw data
    Graphics::typeDrawData mInventoryDrawData;
    Graphics::typeDrawData mSelectorDrawData;
    // Positions
    const std::array<SDL_FPoint, 30> mSlotDefaultPosition; // Base offsets of all positions
    std::array<SDL_FRect, 30>        mSlotPosition;        // Positions based on resolution
    Common::typeScale                mScale;
    Graphics::Texture*&              pUserInterface; // A reference to the userinterface icon.
};
}