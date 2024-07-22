#include <common/sdl.hpp>
#include <object/warp.hpp>

namespace Objects {

Warp::Warp(const Level::type3DMapCoordinate& level,
           const Level::type2DMapCoordinate& destination)
  : mLevel(level)
  , mDestination(destination) {}

Warp::~Warp() {}

Level::type3DMapCoordinate
Warp::getLevel() const {
    return mLevel;
}

Level::type2DMapCoordinate
Warp::getDestination() const {
    return mDestination;
}


}