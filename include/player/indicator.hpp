#pragma once
#include <SDL.h>
#include <common/scale.hpp>
#include <graphics/types/UserInterfaceTexture.hpp>
#include <graphics/types/drawData.hpp>

namespace Player {
/**
 * @brief Class to hold UI elements such as health and energy pool
 */
class Indicator {
  public:
    /**
     * @brief Constructor
     * @param value Reference to the value that will be used
     * @param maxValue Reference to the max value that value can have
     * @param scale Scaling factor of game
     * @param base Base texture
     * @param indicator Indicator texture
     */
    Indicator(int&                            value,
              int&                            maxValue,
              Common::typeScale&              scale,
              Graphics::UserInterfaceTexture* base,
              Graphics::UserInterfaceTexture* indicator);
    void updateIndicator();

    /**
     *
     * @return
     */
    [[nodiscard]] std::vector<Graphics::typeDrawData> getIndicator();

  protected:
  private:
    int&                   mValue;                // Players current value
    int&                   mMaxValue;             // Players current max value
    SDL_FRect              mBaseDestination;      // Destination for background
    SDL_FRect              mIndicatorDestination; // Destination for indication bar
    Graphics::typeDrawData mBaseDrawData;         // Draw data for base
    Graphics::typeDrawData mIndicatorDrawData;    // Draw data for indicator

    Common::typeScale&              mScale;     // Current game scaling
    Graphics::UserInterfaceTexture* pBase;      // Base graphic
    Graphics::UserInterfaceTexture* pIndicator; // Indicator graphic
};
}