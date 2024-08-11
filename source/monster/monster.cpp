#include <monster/monster.hpp>

namespace Monster {
BaseMonster::BaseMonster(const int&                                                         health,
                         const float&                                                       velocity,
                         SDL_FPoint&                                                        playerCenter,
                         std::function<bool(const SDL_FPoint&, const float&, const float&)> checkWalls)
  : mInflictDamage(true)
  , mHealth(health)
  , mVelocity(velocity)
  , mTicks(0)
  , pCurrentTexture(nullptr)
  , pCurrentViewport(nullptr)
  , mPlayerCenter(playerCenter)
  , mState(Objects::IDLE)
  , mDirection(SOUTH)
  , fCheckWalls(checkWalls)
  , DEATH_ANIMATION(20) {}

BaseMonster::BaseMonster(const Monster::BaseMonster& other)
  : mHealth(other.mHealth)
  , mVelocity(other.mVelocity)
  , mState(other.mState)
  , mTextures(other.mTextures)
  , mMonsterPosition{}
  , mDirection(SOUTH)
  , fCheckWalls(other.fCheckWalls)
  , mInflictDamage(false)
  , pCurrentTexture(other.pCurrentTexture)
  , pCurrentViewport(other.pCurrentViewport)
  , mPlayerCenter(other.mPlayerCenter)
  , mTicks(0)
  , DEATH_ANIMATION(20) {}

BaseMonster::~BaseMonster() = default;

void
BaseMonster::damageMonster(const int& damage) {
    mHealth -= damage;
    if (mHealth < 0) {
        mState = Objects::DYING;
        updateReferences();
    }
}

bool
BaseMonster::inflictDamage() const {
    return mInflictDamage;
}

void
BaseMonster::addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture) {
    if (pCurrentTexture == nullptr || pCurrentViewport == nullptr) {
        pCurrentTexture  = texture->getTexture();
        pCurrentViewport = texture->getAnimatedViewport();
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

void
BaseMonster::updatePosition(const float& x, const float& y) {
    mMonsterPosition.x += x;
    mMonsterPosition.y += y;
    mMonsterCenter.x += x;
    mMonsterCenter.y += y;
}

Graphics::typeDrawData
BaseMonster::getMonster() {
    interact();
    return Graphics::typeDrawData{ pCurrentTexture, pCurrentViewport, &mMonsterPosition };
}

SDL_FRect*
BaseMonster::getPosition() {
    return &mMonsterPosition;
}

void
BaseMonster::setAction(Objects::State action) {
    mState = action;
    updateReferences();
}

Objects::State
BaseMonster::getState() {
    if (mState == Objects::DYING) {
        if (mTicks++ > DEATH_ANIMATION)
            mState = Objects::DEAD;
    }
    return mState;
}

void
BaseMonster::updateReferences() {
    pCurrentTexture  = mTextures[{ mState, mDirection }]->getTexture();
    pCurrentViewport = mTextures[{ mState, mDirection }]->getAnimatedViewport();
}

}