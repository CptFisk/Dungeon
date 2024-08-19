#include <global.hpp>
#include <player/indicator.hpp>
#include <utility/math.hpp>

namespace Player {
Indicator::Indicator(int&                   value,
                     Common::typeScale&     scale,
                     const int&             marginBottom,
                     Graphics::BaseTexture* base,
                     Graphics::BaseTexture* indicator)
  : mValue(value)
  , mScale(scale)
  , mMarginBottom(marginBottom)
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
    const auto wB           = pBase->getWidth();
    const auto hB           = pBase->getHeight();
    const auto marginBottom = INT(FLOAT(mScale.windowHeight) / mScale.selectedScale) - mMarginBottom;
    mBaseDestination        = { 16, FLOAT(marginBottom), FLOAT(wB), FLOAT(hB) };

    // Positions for Indicator
    const auto wI = pIndicator->getWidth();
    const auto hI = pIndicator->getHeight();
    mIndicatorDestination         = { 16, FLOAT(marginBottom), FLOAT(wI), FLOAT(hI) };
}

std::vector<Graphics::typeDrawData>
Indicator::getIndicator() {
    return std::vector<Graphics::typeDrawData>{ mBaseDrawData, mIndicatorDrawData };
}

}