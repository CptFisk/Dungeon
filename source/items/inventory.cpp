#include <items/inventory.hpp>

namespace Items {

Inventory::Inventory(Common::typeScale& scale, Graphics::UserInterfaceTexture* inventory, Graphics::UserInterfaceTexture* selector)
  : // Graphical bindings
  mScale(scale)
  , mInventory(inventory)
  , mInventoryDrawData(inventory->getTexture(), nullptr, &mInventoryPosition)
  , mSelector(selector)
  , mSelectorDrawData(selector->getTexture(), nullptr, &mSelectorPosition)
  , mVisible(false)
  , mSelected(0)
  , mSlots{ // Character
            Slot{ SlotType::Amulet, 0 },
            Slot{ SlotType::Head, 0 },
            Slot{ SlotType::Left, 0 },
            Slot{ SlotType::Chest, 0 },
            Slot{ SlotType::Right, 0 },
            Slot{ SlotType::Boots, 0 },
            // Bag
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            Slot{ SlotType::Bag, 0 },
            // Spells
            Slot{ SlotType::Spell, 0 },
            Slot{ SlotType::Spell, 0 },
            Slot{ SlotType::Spell, 0 },
            Slot{ SlotType::Spell, 0 },
            Slot{ SlotType::Spell, 0 },
            Slot{ SlotType::Spell, 0 },
            Slot{ SlotType::Spell, 0 },
            Slot{ SlotType::Spell, 0 }
  } {
    calculatePositions();
}

Graphics::typeDrawData
Inventory::getInventory() {
    return mInventoryDrawData;
}

void
Inventory::calculatePositions() {
    // The idea is to first center the inventory element on the screen.
    const auto screenCenterX = mScale.windowWidthF / 2.0f;
    const auto screenCenterY = mScale.windowHeightF / 2.0f;
    const auto uiCenterX     = mInventory->getWidthF() / 2.0f;
    const auto uiCenterY     = mInventory->getHeightF() / 2.0f;
    // Calculations
    mInventoryPosition.x = screenCenterX - uiCenterX;
    mInventoryPosition.y = screenCenterY - uiCenterY;
    mInventoryPosition.w = mInventory->getWidthF();
    mInventoryPosition.h = mInventory->getHeightF();
}

}