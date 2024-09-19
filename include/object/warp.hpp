#pragma once
#include <SDL.h>
#include <common/coordinates.hpp>
#include <string>

namespace Objects {
class Warp {
  public:
    Warp(const Common::type3DMapCoordinate& level,
         const Common::type2DMapCoordinate& destination);
    ~Warp();

    /**
     * @brief Return the level that is the destination
     */
    [[nodiscard]] Common::type3DMapCoordinate getLevel() const;
    /**
     * @brief Return the destination on the level
     */
    [[nodiscard]] Common::type2DMapCoordinate getDestination() const;
    /**
     * @brief Return the level, but as a string
     */
  protected:
  private:
    const Common::type2DMapCoordinate mDestination;
    const Common::type3DMapCoordinate mLevel;
};
}