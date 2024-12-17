#pragma once
#include <array>
#include <common/scale.hpp>
#include <graphics/types/drawData.hpp>
#include <graphics/types/userInterfaceTexture.hpp>
#include <items/slots.hpp>

namespace Items {

class Inventory {
  public:
    Inventory(Common::typeScale& scale, Graphics::UserInterfaceTexture* inventory, Graphics::UserInterfaceTexture* selector);
    ~Inventory();

    std::array<Graphics::typeDrawData, 2> getInventory();
    /**
     * @brief Using the mouse to click on a specific square.
     * @param x
     * @param y
     */
    void selectItemMouse(const float& x, const float& y);

  protected:
    void calculatePositions(); // Used to calulcate positions for all graphical elements
  private:
    SDL_FPoint           mTopLeft;  //Top left coordinate of inventory, used to calculate offsets
    uint8_t             mSelected;
    std::array<Slot, 30> mSlots;
    // Graphics
    Graphics::UserInterfaceTexture* mInventory;
    Graphics::UserInterfaceTexture* mSelector;
    // Draw data
    Graphics::typeDrawData mInventoryDrawData;
    Graphics::typeDrawData mSelectorDrawData;
    // Positions
    const std::array<SDL_FPoint, 30> mSelectorDefaultPositions; // Base offsets of all positions
    std::array<SDL_FRect, 30>        mSelectorPositions;        // Positions based on resolution
    Common::typeScale                mScale;
};
}