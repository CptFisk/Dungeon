#include <common/sdl.hpp>
#include <object/warp.hpp>

namespace Objects {

Warp::Warp(const Level::File::typeWarpData& data)
  : mDestination(data.Destination)
  , mFile(data.Filename) {
    mPosition = Common::newSDL_FRect(data.Origin.X, data.Origin.Y);
}

Warp::~Warp() {}

Level::File::typeWarpCoordinate
Warp::getDestination() const {
    return mDestination;
}

std::string
Warp::getFilename() const {
    return mFile;
}

SDL_FRect&
Warp::getPosition() {
    return mPosition;
}

}