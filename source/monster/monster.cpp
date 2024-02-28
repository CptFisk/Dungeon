#include <monster/monster.hpp>

namespace Monster {
BaseMonster::BaseMonster(const int& health, const float& velocity)
  : mHealth(health)
  , mVelocity(velocity)
  , mCurrentTexture(nullptr)
  , mCurrentViewport(nullptr)
  , mAction(Objects::IDLE)
  , mDirection(South) {}

BaseMonster::BaseMonster(const Monster::BaseMonster& other)
  : mHealth(other.mHealth)
  , mVelocity(other.mVelocity) {}

BaseMonster::~BaseMonster() = default;

BaseMonster*
BaseMonster::spawn() const {
    return new BaseMonster(*this);
}

bool
BaseMonster::damage(const int& damage) {
    if (mHealth -= damage <= 0)
        return true;
    return false;
}

void
BaseMonster::addAnimatedTexture(Objects::ObjectAction action, Directions direction, Graphics::AnimatedTexture* texture) {
    mTextures[{ action, direction }] = texture;
    if (mCurrentTexture == nullptr || mCurrentViewport == nullptr) {
        mCurrentTexture  = texture->mTexture;
        mCurrentViewport = texture->getViewport();
    }
}

void
BaseMonster::setDirection(Directions direction) {
    mDirection = direction;
    updateReferences();
}

void
BaseMonster::setAction(Objects::ObjectAction action) {
    mAction = action;
    updateReferences();
}

void
BaseMonster::updateReferences() {
    mCurrentTexture  = mTextures[{ mAction, mDirection }]->getTexture();
    mCurrentViewport = mTextures[{ mAction, mDirection }]->getViewport();
}

}