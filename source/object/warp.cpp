#include <common/sdl.hpp>
#include <object/warp.hpp>

namespace Objects {

Warp::Warp(const Level::File::typeMapCoordinate& level,
           const Level::File::typeMapCoordinate& destination)
  : mLevel(level)
  , mDestination(destination)
  , mFilename(destination.toString()) {}

Warp::~Warp() {}

Level::File::typeMapCoordinate
Warp::getLevel() const {
    return mLevel;
}

Level::File::typeMapCoordinate
Warp::getDestination() const {
    return mDestination;
}

std::string
Warp::getFilename() const {
    return mFilename;
}

}