#include <common/sdl.hpp>
#include <object/warp.hpp>

namespace Objects {

Warp::Warp(const Common::type3DMapCoordinate& level,
           const Common::type2DMapCoordinate& destination)
  : mLevel(level)
  , mDestination(destination) {}

Warp::~Warp() {}

Common::type3DMapCoordinate
Warp::getLevel() const {
    return mLevel;
}

Common::type2DMapCoordinate
Warp::getDestination() const {
    return mDestination;
}


}