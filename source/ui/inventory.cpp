#include <ui/userInterface.hpp>

namespace Engine::UI{

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
    //if (mSelectorVisible)
        data.push_back(mSelectorDrawData); // Final item
    return data;
}

void
UserInterface::updateInventory() {
    const auto [x,y] = calculateCenter();
    const auto uiCenterX     = pInventory->getWidthF() / 2.0f;
    const auto uiCenterY     = pInventory->getHeightF() / 2.0f;
    //Calculate top left position
    const auto  topLeft = SDL_FPoint{x - uiCenterX, y -uiCenterY};
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