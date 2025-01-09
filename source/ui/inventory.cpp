#include <ui/userInterface.hpp>
#include <utility/textures.hpp>
namespace Engine::UI {

std::vector<Graphics::typeDrawData>
UserInterface::getInventory() {
    std::vector<Graphics::typeDrawData> data = { mInventoryBackgroundDrawData };
    int                                 pos  = 0;
    for (auto& slot : mInventorySlots) {
        if (slot.Item != nullptr) {
            data.emplace_back(slot.Item->getTexture(), nullptr, &mInventoryPositions.at(pos));
        }
        pos++;
    }
    if (mInventorySelectorVisible)
        data.push_back(mInventorySelectorDrawData); // Final item
    return data;
}

std::optional<uint8_t>
UserInterface::selectItemMouse(const SDL_FPoint& point) {
    uint8_t index = {};
    for (const auto& position : mInventoryPositions) {
        if (Utility::isOverlapping(point, position)) {
            mInventorySelectorDrawData.Position = &mInventoryPositions.at(index);
            return index;
        }
        index++;
    }
    return std::nullopt;
}

bool&
UserInterface::getSelectorVisible() {
    return mInventorySelectorVisible;
}

void
UserInterface::updateInventory() {
    const auto [x, y]    = calculateCenter();
    const auto uiCenterX = pInventoryBackground->getWidthF() / 2.0f;
    const auto uiCenterY = pInventoryBackground->getHeightF() / 2.0f;
    // Calculate top left position
    const auto topLeft = SDL_FPoint{ x - uiCenterX, y - uiCenterY };
    // Calculations
    mInventoryBackgroundDrawData.Position->x = topLeft.x;
    mInventoryBackgroundDrawData.Position->y = topLeft.y;
    mInventoryBackgroundDrawData.Position->w = pInventoryBackground->getWidthF();
    mInventoryBackgroundDrawData.Position->h = pInventoryBackground->getHeightF();
    // Assign positions
    for (auto i = 0; i < mInventoryPositions.size(); i++) {
        mInventoryPositions.at(i).x = topLeft.x + mInventoryDefaultPosition.at(i).x;
        mInventoryPositions.at(i).y = topLeft.y + mInventoryDefaultPosition.at(i).y;
        mInventoryPositions.at(i).w = pInventorySelector->getWidthF();
        mInventoryPositions.at(i).h = pInventorySelector->getHeightF();
    }
}

}