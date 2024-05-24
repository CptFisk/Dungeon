#include <objects/door.hpp>

namespace Objects {

Door::Door(const Graphics::typeSimpleTexture& graphic, const Graphics::AnimatedTexture& animatedGraphic, bool open)
  : mOpen(open)
  , mGraphic(graphic)
  , mAnimatedGraphic(animatedGraphic) {


}

Door::~Door() {}

void
Door::open(bool condition) {
    mOpen = !mOpen && condition;
}

Common::typeDrawData&
Door::getDrawData() {
    return mDrawData;
}

}