#include <ui/userInterface.hpp>
#include <utility/textures.hpp>
namespace Engine::UI {

std::vector<Graphics::typeDrawData>
UserInterface::getInventory() {
    std::vector<Graphics::typeDrawData> data = { mInventoryDrawData };
    int                                 pos  = 0;
    for (auto& slot : mSlots) {
        if (slot.Item != nullptr) {
            data.emplace_back(slot.Item->getTexture(), nullptr, &mInventoryPositions.at(pos));
        }
        pos++;
    }
    if (mSelectorVisible)
        data.push_back(mSelectorDrawData); // Final item
    return data;
}

std::optional<uint8_t>
UserInterface::selectItemMouse(const SDL_FPoint& point) {
    uint8_t index = {};
    for (const auto& position : mInventoryPositions) {
        if (Utility::isOverlapping(point, position)) {
            mSelectorDrawData.Position = &mInventoryPositions.at(index);
            return index;
        }
        index++;
    }
    return std::nullopt;
}

bool&
UserInterface::getSelectorVisible() {
    return mSelectorVisible;
}

void
UserInterface::updateInventory() {
    const auto [x, y]    = calculateCenter();
    const auto uiCenterX = pInventory->getWidthF() / 2.0f;
    const auto uiCenterY = pInventory->getHeightF() / 2.0f;
    // Calculate top left position
    const auto topLeft = SDL_FPoint{ x - uiCenterX, y - uiCenterY };
    // Calculations
    mInventoryDrawData.Position->x = topLeft.x;
    mInventoryDrawData.Position->y = topLeft.y;
    mInventoryDrawData.Position->w = pInventory->getWidthF();
    mInventoryDrawData.Position->h = pInventory->getHeightF();
    // Assign positions
    for (auto i = 0; i < mInventoryPositions.size(); i++) {
        mInventoryPositions.at(i).x = topLeft.x + mInventoryDefaultPosition.at(i).x;
        mInventoryPositions.at(i).y = topLeft.y + mInventoryDefaultPosition.at(i).y;
        mInventoryPositions.at(i).w = pSelector->getWidthF();
        mInventoryPositions.at(i).h = pSelector->getHeightF();
    }
}

}