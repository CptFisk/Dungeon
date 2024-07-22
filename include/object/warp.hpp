#pragma once
#include <SDL.h>
#include <level/types/warp.hpp>
#include <string>

namespace Objects {
class Warp {
  public:
    Warp(const Level::type3DMapCoordinate& level,
         const Level::type2DMapCoordinate& destination);
    ~Warp();

    /**
     * @brief Return the level that is the destination
     */
    [[nodiscard]] Level::type3DMapCoordinate getLevel() const;
    /**
     * @brief Return the destination on the level
     */
    [[nodiscard]] Level::type2DMapCoordinate getDestination() const;
    /**
     * @brief Return the level, but as a string
     */
  protected:
  private:
    const Level::type2DMapCoordinate mDestination;
    const Level::type3DMapCoordinate mLevel;
};
}