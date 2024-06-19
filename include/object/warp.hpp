#pragma once
#include <SDL.h>
#include <level/types/warp.hpp>
#include <string>

namespace Objects {
class Warp {
  public:
    Warp(const Level::File::typeWarpData& data);
    ~Warp();

    Level::File::typeWarpCoordinate getDestination() const;
    std::string                     getFilename() const;
    /**
     * @brief Return the position that the warp is located at
     */
    SDL_FRect& getPosition();
  protected:
  private:
    SDL_FRect                             mPosition;
    const Level::File::typeWarpCoordinate mDestination;
    const std::string                     mFile;
};
}