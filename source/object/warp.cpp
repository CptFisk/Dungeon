#include <common/sdl.hpp>
#include <object/warp.hpp>

namespace Objects {

Warp::Warp(const Level::File::type3DMapCoordinate& level,
           const Level::File::type2DMapCoordinate& destination)
  : mLevel(level)
  , mDestination(destination) {}

Warp::~Warp() {}

Level::File::type3DMapCoordinate
Warp::getLevel() const {
    return mLevel;
}

Level::File::type2DMapCoordinate
Warp::getDestination() const {
    return mDestination;
}


}