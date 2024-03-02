#include <monster/monster.hpp>

namespace Monster {
BaseMonster::BaseMonster(const int& health, const float& velocity, SDL_FRect* playerPosition)
  : mInflictDamage(true)
  , mHealth(health)
  , mVelocity(velocity)
  , mTicks(0)
  , pCurrentTexture(nullptr)
  , pCurrentViewport(nullptr)
  , pPlayerPosition(playerPosition)
  , mState(Objects::IDLE)
  , mDirection(SOUTH)
  , DEATH_ANIMATION(20) {}

BaseMonster::BaseMonster(const Monster::BaseMonster& other)
  : mHealth(other.mHealth)
  , mVelocity(other.mVelocity)
  , mState(other.mState)
  , mTextures(other.mTextures)
  , mMonsterPosition({ 100.0f, 100.0f, 32.0f, 32.0f })
  , mDirection(SOUTH)
  , mInflictDamage(0)
  , pCurrentTexture(other.pCurrentTexture)
  , pCurrentViewport(other.pCurrentViewport)
  , pPlayerPosition(other.pPlayerPosition)
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
    interact();
    return typeMonsterData{ pCurrentTexture, pCurrentViewport, &mMonsterPosition };
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
        printf("%i | %i\n", mTicks, DEATH_ANIMATION);
        if (mTicks++ > DEATH_ANIMATION)
            mState = Objects::DEAD;
    }
    return mState;
}

void
BaseMonster::updateReferences() {
    pCurrentTexture  = mTextures[{ mState, mDirection }]->getTexture();
    pCurrentViewport = mTextures[{ mState, mDirection }]->getViewport();
}

}