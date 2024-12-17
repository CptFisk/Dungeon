#include <items/inventory.hpp>
#include <utility/textures.hpp>
namespace Items {

Inventory::Inventory(Common::typeScale& scale, Graphics::UserInterfaceTexture* inventory, Graphics::UserInterfaceTexture* selector)
  : // Graphical bindings
  mScale(scale)
  , mSelectorPositions{}
  , mInventory(inventory)
  , mInventoryDrawData(inventory->getTexture(), nullptr, new SDL_FRect (0.0f, 0.0f,0.0f,0.0f))
  , mSelector(selector)
  , mSelectorDrawData(selector->getTexture(), nullptr)
  , mSelected(7)
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
  },
  mSelectorDefaultPositions{
            // Equipment
            SDL_FPoint{ 20, 20 },
            SDL_FPoint{ 40, 20 },
            SDL_FPoint{ 20, 40 },
            SDL_FPoint{ 40, 40 },
            SDL_FPoint{ 60, 40 },
            SDL_FPoint{ 40, 60 },
            //Bags
            SDL_FPoint{ 100, 20 },
            SDL_FPoint{ 120, 20 },
            SDL_FPoint{ 140, 20},
            SDL_FPoint{ 160, 20 },
            SDL_FPoint{ 100, 40 },
            SDL_FPoint{ 120, 40 },
            SDL_FPoint{ 140, 40},
            SDL_FPoint{ 160, 40 },
            SDL_FPoint{ 100, 60 },
            SDL_FPoint{ 120, 60 },
            SDL_FPoint{ 140, 60},
            SDL_FPoint{ 160, 60 },
            SDL_FPoint{ 100, 80 },
            SDL_FPoint{ 120, 80 },
            SDL_FPoint{ 140, 80},
            SDL_FPoint{ 160, 80 },
            //Spells
            SDL_FPoint {20,120},
            SDL_FPoint {40,120},
            SDL_FPoint {60,120},
            SDL_FPoint {80,120},
            SDL_FPoint {100,120},
            SDL_FPoint {120,120},
            SDL_FPoint {140,120},
            SDL_FPoint {160,120}
  } {
    // Selecting first position in bag
    mSelectorDrawData.Position = &mSelectorPositions.at(7);
    calculatePositions();
}

Inventory::~Inventory() {
    // Clear pointer created in draw data
    delete mInventoryDrawData.Position;
}

std::array<Graphics::typeDrawData, 2>
Inventory::getInventory() {
    return { mInventoryDrawData, mSelectorDrawData };
}

void
Inventory::selectItemMouse(const float& x, const float& y) {
    const auto point = SDL_FPoint{ x, y };
    uint8_t    index = {};
    for (const auto& position : mSelectorPositions) {
        if (Utility::isOverlapping(point, position)) {
            mSelectorDrawData.Position = &mSelectorPositions.at(index);
            break;
        }
        index++;
    }
}

void
Inventory::calculatePositions() {
    // The idea is to first center the inventory element on the screen.
    const auto screenCenterX = (mScale.windowWidthF / mScale.selectedScale) / 2.0f;
    const auto screenCenterY = (mScale.windowHeightF / mScale.selectedScale) / 2.0f;
    const auto uiCenterX     = mInventory->getWidthF() / 2.0f;
    const auto uiCenterY     = mInventory->getHeightF() / 2.0f;
    mTopLeft.x               = screenCenterX - uiCenterX; // Used to assign selector positions
    mTopLeft.y               = screenCenterY - uiCenterY;
    // Calculations
    mInventoryDrawData.Position->x = screenCenterX - uiCenterX;
    mInventoryDrawData.Position->y = screenCenterY - uiCenterY;
    mInventoryDrawData.Position->w = mInventory->getWidthF();
    mInventoryDrawData.Position->h = mInventory->getHeightF();
    // Assign positions
    for (auto i = 0; i < mSelectorDefaultPositions.size(); i++) {
        mSelectorPositions.at(i).x = mTopLeft.x + mSelectorDefaultPositions.at(i).x;
        mSelectorPositions.at(i).y = mTopLeft.y + mSelectorDefaultPositions.at(i).y;
        mSelectorPositions.at(i).w = mSelector->getWidthF();
        mSelectorPositions.at(i).h = mSelector->getHeightF();
    }
}
}