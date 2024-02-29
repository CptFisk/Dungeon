#include <monster/monster.hpp>

namespace Monster {
BaseMonster::BaseMonster(const int& health, const float& velocity, SDL_FRect* playerPosition)
  : mInflictDamage(true)
  , mHealth(health)
  , mVelocity(velocity)
  , pCurrentTexture(nullptr)
  , pCurrentViewport(nullptr)
  , pPlayerPosition(playerPosition)
  , mAction(Objects::IDLE)
  , mDirection(SOUTH) {}

BaseMonster::BaseMonster(const Monster::BaseMonster& other)
  : mHealth(other.mHealth)
  , mVelocity(other.mVelocity)
  , mAction(other.mAction)
  , mTextures(other.mTextures)
  , mMonsterPosition({ 100.0f, 100.0f, 32.0f, 32.0f })
  , mDirection(SOUTH)
  , pCurrentTexture(other.pCurrentTexture)
  , pCurrentViewport(other.pCurrentViewport)
  , pPlayerPosition(other.pPlayerPosition) {}

BaseMonster::~BaseMonster() = default;

void
BaseMonster::damageMonster(const int& damage) {
    mHealth -= damage;
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

void
BaseMonster::setAction(Objects::State action) {
    mAction = action;
    updateReferences();
}

void
BaseMonster::updateReferences() {
    pCurrentTexture  = mTextures[{ mAction, mDirection }]->getTexture();
    pCurrentViewport = mTextures[{ mAction, mDirection }]->getViewport();
}

}