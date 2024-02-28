#include <monster/monster.hpp>

namespace Monster {
BaseMonster::BaseMonster(const int& health, const float& velocity)
  : mHealth(health)
  , mVelocity(velocity)
  , pCurrentTexture(nullptr)
  , pCurrentViewport(nullptr)
  , mAction(Objects::IDLE)
  , mDirection(SOUTH) {}

BaseMonster::BaseMonster(const Monster::BaseMonster& other)
  : mHealth(other.mHealth)
  , mVelocity(other.mVelocity)
  , mAction(other.mAction)
  , mTextures(other.mTextures)
  , mMonsterPosition({ 100.0f, 100.0f, 32.0f, 32.0f })
  , pCurrentTexture(other.pCurrentTexture)
  , pCurrentViewport(other.pCurrentViewport) {}

BaseMonster::~BaseMonster() = default;

bool
BaseMonster::damage(const int& damage) {
    if (mHealth -= damage <= 0)
        return true;
    return false;
}

void
BaseMonster::addAnimatedTexture(Objects::ObjectAction action, Directions direction, Graphics::AnimatedTexture* texture) {
    if (pCurrentTexture == nullptr || pCurrentViewport == nullptr) {
        pCurrentTexture  = texture->mTexture;
        pCurrentViewport = texture->getViewport();
    }

    if (direction == Directions::ALL) {
        mTextures[{ action, NORTH }] = texture;
        mTextures[{ action, EAST }]  = texture;
        mTextures[{ action, SOUTH }] = texture;
        mTextures[{ action, WEST }]  = texture;
        return;
    }

    mTextures[{ action, direction }] = texture;
}

void
BaseMonster::setDirection(Directions direction) {
    mDirection = direction;
    updateReferences();
}

typeMonsterData
BaseMonster::getMonster() {
    return typeMonsterData{ pCurrentTexture, pCurrentViewport, &mMonsterPosition };
}

void
BaseMonster::setAction(Objects::ObjectAction action) {
    mAction = action;
    updateReferences();
}

void
BaseMonster::updateReferences() {
    pCurrentTexture  = mTextures[{ mAction, mDirection }]->getTexture();
    pCurrentViewport = mTextures[{ mAction, mDirection }]->getViewport();
}

}