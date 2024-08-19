#pragma once
#include <SDL.h>
#include <common/scale.hpp>
#include <graphics/types/baseTexture.hpp>
#include <graphics/types/drawData.hpp>

namespace Player {
class Indicator {
  public:
    Indicator(int& value, Common::typeScale& scale, const int& marginBottom, Graphics::BaseTexture* base, Graphics::BaseTexture* indicator);
    void updateIndicator();

    /**
     *
     * @return
     */
    [[nodiscard]] std::vector<Graphics::typeDrawData> getIndicator();

  protected:
  private:
    int& mValue; // Players current health

    const int mMarginBottom; // Margin to bottom of screen

    SDL_FRect              mBaseDestination;       // Destination for background
    SDL_FRect              mIndicatorDestination; // Destination for indication bar
    Graphics::typeDrawData mBaseDrawData;          // Draw data for base
    Graphics::typeDrawData mIndicatorDrawData;    // Draw data for indicator

    Common::typeScale&     mScale;     // Current game scaling
    Graphics::BaseTexture* pBase;      // Base graphic
    Graphics::BaseTexture* pIndicator; // Indicator graphic
};
}