#include <global.hpp>
#include <player/indicator.hpp>
#include <utility/math.hpp>

namespace Player {
Indicator::Indicator(int& value, Common::typeScale& scale, Graphics::UserInterfaceTexture* base, Graphics::UserInterfaceTexture* indicator)
  : mValue(value)
  , mScale(scale)
  , pBase(base)
  , pIndicator(indicator)
  , mBaseDestination{}
  , mIndicatorDestination{}
  , mBaseDrawData(base->getTexture(), nullptr, &mBaseDestination)
  , mIndicatorDrawData(indicator->getTexture(), nullptr, &mIndicatorDestination) {
    updateIndicator(); // Calculate position
}

void
Indicator::updateIndicator() {
    // Positions for base-element
    mBaseDestination = { pBase->getMarginLeftF(),
                         FLOAT(INT(FLOAT(mScale.windowHeight) / mScale.selectedScale) - pBase->getMarginBottom()),
                         pBase->getWidthF(),
                         pBase->getHeightF() };

    // Positions for Indicator
    mIndicatorDestination = { pIndicator->getMarginLeftF(),
                              FLOAT(INT(FLOAT(mScale.windowHeight) / mScale.selectedScale) - pIndicator->getMarginBottom()),
                              pIndicator->getWidthF(),
                              pIndicator->getHeightF() };
}

std::vector<Graphics::typeDrawData>
Indicator::getIndicator() {
    return std::vector<Graphics::typeDrawData>{ mBaseDrawData, mIndicatorDrawData };
}

}