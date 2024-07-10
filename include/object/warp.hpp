#pragma once
#include <SDL.h>
#include <level/types/warp.hpp>
#include <string>

namespace Objects {
class Warp {
  public:
    Warp(const Level::File::typeMapCoordinate& level,
         const Level::File::typeMapCoordinate& destination);
    ~Warp();

    /**
     * @brief Return the level that is the destination
     */
    [[nodiscard]] Level::File::typeMapCoordinate getLevel() const;
    /**
     * @brief Return the destination on the level
     */
    [[nodiscard]] Level::File::typeMapCoordinate getDestination() const;
    /**
     * @brief Return the level, but as a string
     */
    [[nodiscard]] std::string getFilename() const;
  protected:
  private:
    const Level::File::typeMapCoordinate mDestination;
    const Level::File::typeMapCoordinate mLevel;
    const std::string mFilename;
};
}