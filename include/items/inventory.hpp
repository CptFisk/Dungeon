#pragma once
#include <array>
#include <graphics/types/userInterfaceTexture.hpp>
#include <graphics/types/drawData.hpp>
#include <items/slots.hpp>
#include <common/scale.hpp>

namespace Items {

class Inventory {
  public:
    Inventory(Common::typeScale& scale, Graphics::UserInterfaceTexture* inventory, Graphics::UserInterfaceTexture* selector);
    ~Inventory() = default;

    Graphics::typeDrawData getInventory();

  protected:
    void calculatePositions();  //Used to calulcate positions for all graphical elements
  private:
    bool                            mVisible;
    uint16_t                        mSelected;
    std::array<Slot, 30>            mSlots;
    //Graphics
    Graphics::UserInterfaceTexture* mInventory;
    Graphics::UserInterfaceTexture* mSelector;
    //Draw data
    Graphics::typeDrawData mInventoryDrawData;
    Graphics::typeDrawData mSelectorDrawData;
    //Positions
    SDL_FRect mInventoryPosition;
    SDL_FRect mSelectorPosition;
    Common::typeScale mScale;
};
}