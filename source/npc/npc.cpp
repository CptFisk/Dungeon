#include <npc/npc.hpp>

namespace NPC {

BaseNPC::BaseNPC(const float& width, const float& height, std::function<bool(const SDL_FPoint&, const float&, const float&)>& checkWalls)
  : mVelocity(0.2f)
  , mNPCWidth(width)
  , mNPCHeight(height)
  , fCheckWalls(checkWalls)
  , mState(Objects::IDLE)
  , mDirection(SOUTH)
  , pCurrentTexture(nullptr)
  , pCurrentViewport(nullptr) {}

BaseNPC::BaseNPC(const NPC::BaseNPC& other)
  : mVelocity(other.mVelocity)
  , mNPCWidth(other.mNPCWidth)
  , mNPCHeight(other.mNPCHeight)
  , fCheckWalls(other.fCheckWalls)
  , mState(other.mState)
  , mDirection(other.mDirection)
  , mTextures(other.mTextures)
  , pCurrentTexture(other.pCurrentTexture)
  , pCurrentViewport(other.pCurrentViewport) {}

BaseNPC::~BaseNPC() = default;

void
BaseNPC::addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture) {
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
BaseNPC::setDirection(Directions direction) {
    mDirection = direction;
    updateReferences();
}

void
BaseNPC::updatePosition(const float& x, const float& y) {
    mNPCPosition.x += x;
    mNPCPosition.y += y;
    mNPCCenter.x += x;
    mNPCCenter.y += y;
}

Graphics::typeDrawData
BaseNPC::getNpc() {
    interact();
    return Graphics::typeDrawData{ pCurrentTexture, pCurrentViewport, &mNPCPosition };
}

SDL_FRect*
BaseNPC::getPosition() {
    return &mNPCPosition;
}

void
BaseNPC::setAction(Objects::State action) {
    mState = action;
    updateReferences();
}

Objects::State
BaseNPC::getState() {
    return mState;
}

void
BaseNPC::updateReferences() {
    pCurrentTexture  = mTextures[{ mState, mDirection }]->getTexture();
    pCurrentViewport = mTextures[{ mState, mDirection }]->getAnimatedViewport();
}

}