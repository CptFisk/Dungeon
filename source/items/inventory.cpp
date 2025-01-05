#include <error.hpp>
#include <items/inventory.hpp>
#include <items/weapon.hpp>
#include <utility/textures.hpp>

namespace Items {

Inventory::Inventory(Common::typeScale& scale, Graphics::UserInterfaceTexture* inventory, Graphics::UserInterfaceTexture* selector, Graphics::Texture*& userinterface)
  : // Graphical bindings
  mScale(scale)
  , mTopLeft{}
  , mSlotPosition{}
  , mInventory(inventory)
  , mInventoryDrawData(inventory->getTexture(), nullptr, new SDL_FRect (0.0f, 0.0f,0.0f,0.0f))
  , mSelector(selector)
  , mSelectorDrawData(selector->getTexture(), nullptr)
  , mSelected(6)
  , mSelectorVisible(false)
  , pUserInterface(userinterface)
  , mItemStats{}
  , mSlots{ // Character
            Slot(SlotType::Amulet),
            Slot( SlotType::Head),
            Slot( SlotType::Left),
            Slot( SlotType::Chest),
            Slot( SlotType::Right),
            Slot( SlotType::Boots),
            // Bag
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            Slot( SlotType::Bag),
            // Spells
            Slot( SlotType::Spell),
            Slot( SlotType::Spell),
            Slot( SlotType::Spell),
            Slot( SlotType::Spell),
            Slot( SlotType::Spell),
            Slot( SlotType::Spell),
            Slot( SlotType::Spell),
            Slot( SlotType::Spell)
  },
  mSlotDefaultPosition{
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
    calculatePositions();
    // Selecting first position in bag
    mSelectorDrawData.Position = &mSlotPosition.at(mSelected);
}

Inventory::~Inventory() {
    // Clear pointer created in draw data
    delete mInventoryDrawData.Position;
}

std::vector<Graphics::typeDrawData>
Inventory::getInventory() {
    // Start with the background
    std::vector<Graphics::typeDrawData> data = { mInventoryDrawData };
    int                                 pos  = 0;
    for (auto& slot : mSlots) {
        if (slot.Item != nullptr) {
            data.emplace_back(slot.Item->getTexture(), nullptr, &mSlotPosition.at(pos));
        }
        pos++;
    }
    if (mSelectorVisible)
        data.push_back(mSelectorDrawData); // Final item
    return data;
}

void
Inventory::selectItemMouse(const SDL_FPoint& point) {
    uint8_t index = {};
    for (const auto& position : mSlotPosition) {
        if (Utility::isOverlapping(point, position)) {
            if (swap(mSelectorVisible, mSelected, index)) {
                mSelectorVisible = false;
            } else {
                mSelectorVisible = true;
            }
            mSelectorDrawData.Position = &mSlotPosition.at(index);
            mSelected                  = index;
            break;
        }
        index++;
    }
}

void
Inventory::addItem(Items::Item*& item) {
    ASSERT_WITH_MESSAGE(item == nullptr, "Item is nullptr");
    const int     startIndex = 6;
    constexpr int endIndex   = startIndex + 16;
    for (int i = startIndex; i < endIndex; i++) {
        if (mSlots[i].Item == nullptr) {
            mSlots[i].Item = item;
            break;
        }
    }
}

bool
Inventory::equipItem(const uint16_t& itemId) {
    Item* item = nullptr;
    // Bag index
    const int     startIndex = 6;
    constexpr int endIndex   = startIndex + 16;
    int           position   = {}; // If we find the item, this is the position
    for (int i = startIndex; i < endIndex; i++) {
        if (mSlots[i].Item && mSlots[i].Item->getId() == itemId) {
            item     = mSlots[i].Item;
            position = i;
            break;
        }
    }
    // Item was not found
    if (!item)
        return false;
    // Check what slot we shall equip in
    return swap(true, position, getSlotId(item->getSlotType()));
}

void
Inventory::calculateStats() {
    mItemStats = {}; // Make it zero
    for (auto i = 0; i < 6; i++) {
        if (mSlots[i].Item != nullptr)
            mItemStats += mSlots[i].Item->getStats();
    }
}

Stats::Stats&
Inventory::getItemStats() {
    mItemStats;
}

bool
Inventory::swap(const bool& enabled, const int& index1, const int& index2) {
    auto item1 = mSlots.at(index1);
    auto item2 = mSlots.at(index2);
    if (item1.Item == nullptr || index1 == index2 || !enabled)
        return false;
    // Can we even move item1 to item 2
    if (item1.Item->getSlotType() == item2.Type || item2.Type == Items::SlotType::Bag) {
        if (item2.Item != nullptr) {
            mSlots.at(index2).Item = item1.Item;
            mSlots.at(index1).Item = item2.Item;
        } else {
            mSlots.at(index2).Item = item1.Item;
            mSlots.at(index1).Item = nullptr;
        }
        return true;
    }
    return false;
}

WeaponType
Inventory::getWeapon(const int& index) {
    if (mSlots.at(index).Item == nullptr)
        return WeaponType::None;
    auto weapon = dynamic_cast<Weapon*>(mSlots.at(index).Item);
    return weapon->getWeaponType();
}

WeaponType
Inventory::getLeftWeapon() {
    // Slot 2 = left, 4 = right
    return getWeapon(2);
}

WeaponType
Inventory::getRightWeapon() {
    // Slot 2 = left, 4 = right
    return getWeapon(4);
}

int
Inventory::getSlotId(const Items::SlotType& slot) {
    switch (slot) {
        case SlotType::Amulet:
            return 0;
        case SlotType::Head:
            return 1;
        case SlotType::Left:
            return 2;
        case SlotType::Chest:
            return 3;
        case SlotType::Right:
            return 4;
        case SlotType::Boots:
            return 5;
        default:
            return 7; // Bag
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
    for (auto i = 0; i < mSlotDefaultPosition.size(); i++) {
        mSlotPosition.at(i).x = mTopLeft.x + mSlotDefaultPosition.at(i).x;
        mSlotPosition.at(i).y = mTopLeft.y + mSlotDefaultPosition.at(i).y;
        mSlotPosition.at(i).w = mSelector->getWidthF();
        mSlotPosition.at(i).h = mSelector->getHeightF();
    }
}
}