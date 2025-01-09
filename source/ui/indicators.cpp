#include <ui/userInterface.hpp>

namespace Engine::UI{

std::vector<Graphics::typeDrawData>
UserInterface::getIndicators() const {
    return mIndicatorsDrawData;
}

void
UserInterface::updateIndicators() {
    auto& hotkeyPosition = mIndicatorsDrawData.front().Position;
    hotkeyPosition->x    = pIndicatorBackground->getMarginLeftF();
    hotkeyPosition->y    = pIndicatorBackground->getMarginTopF();
    hotkeyPosition->w    = pIndicatorBackground->getWidthF();
    hotkeyPosition->h    = pIndicatorBackground->getHeightF();

    // Red bar background
    auto& redBg = mIndicatorsDrawData.at(1).Position;
    redBg->x    = hotkeyPosition->x + hotkeyPosition->w + 4;
    redBg->y    = hotkeyPosition->y + 1.0f;
    redBg->w    = calculateLength(mPlayerStats.Vitality);
    redBg->h    = 4.0f;

    // Green bar background
    auto& greenBg = mIndicatorsDrawData.at(2).Position;
    greenBg->x    = redBg->x;
    greenBg->y    = redBg->y + 5.0f;
    greenBg->w    = calculateLength(mPlayerStats.Stamina);
    greenBg->h    = 4.0f;

    // Yellow bar background
    auto& yellowBg = mIndicatorsDrawData.at(3).Position;
    yellowBg->x    = greenBg->x;
    yellowBg->y    = greenBg->y + 5.0f;
    yellowBg->w    = 52.0f;
    yellowBg->h    = 4.0f;

    // Red bar
    auto& redBar = mIndicatorsDrawData.at(4).Position;
    redBar->x    = redBg->x + 1.0f;
    redBar->y    = redBg->y + 1.0f;
    redBar->w    = 10.0f;
    redBar->h    = 2.0f;

    // Green bar
    auto& greenBar = mIndicatorsDrawData.at(4).Position;
    greenBar->x    = greenBg->x + 1.0f;
    greenBar->y    = greenBg->y + 1.0f;
    greenBar->w    = 10.0f;
    greenBar->h    = 2.0f;

    // Yellow bar
    auto& yellowBar = mIndicatorsDrawData.at(5).Position;
    yellowBar->x    = yellowBg->x + 1.0f;
    yellowBar->y    = yellowBg->y + 1.0f;
    yellowBar->w    = 50.0f;
    yellowBar->h    = 2.0f;
}

void
UserInterface::updateBars() {}

}