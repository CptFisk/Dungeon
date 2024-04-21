#include <player/player.hpp>

namespace Player {
Player::Player()
  : mTexturePosition(64.0f, 50.0f, 16.0f, 16.0f)
  , mCurrentTexture(nullptr)
  , mCurrentViewport(nullptr)
  , mAction(Objects::IDLE)
  , mDirection(SOUTH)
  , mMomentum(0.0f) {}

Player::~Player() = default;

SDL_FRect*
Player::getTexturePosition() {
    return &mTexturePosition;
}

SDL_Texture**
Player::getTexture() {
    return &mCurrentTexture;
}

SDL_FRect**
Player::getTextureViewport() {
    return &mCurrentViewport;
}

void
Player::addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture) {
    mTextures[{ action, direction }] = texture;
    if (mCurrentTexture == nullptr || mCurrentViewport == nullptr) {
        mCurrentTexture = texture->mTexture;
        mCurrentViewport = texture->getViewport();
    }
}

void
Player::updateReferences() {
    mCurrentTexture = mTextures[{ mAction, mDirection }]->getTexture();
    mCurrentViewport = mTextures[{ mAction, mDirection }]->getViewport();
}

void
Player::setAction(Objects::State action) {
    mAction = action;
    updateReferences();
}

void
Player::setDirection(Directions direction) {
    mDirection = direction;
    updateReferences();
}

void
Player::resetMomentum() {
    mMomentum = 0.1f;
}

float
Player::move(Directions direction) {
    if(mMomentum <= 1.0f)
        mMomentum += 0.1;
    switch (direction) {
        case NORTH:
            mTexturePosition.y -= mMomentum;
            break;
        case EAST:
            mTexturePosition.x += mMomentum;
            break;
        case SOUTH:
            mTexturePosition.y += mMomentum;
            break;
        case WEST:
            mTexturePosition.x -=mMomentum;
            break;
        case ALL:
        default:
            break;
    }
    mAction    = Objects::MOVE;
    mDirection = direction;
    updateReferences();
    return mMomentum;
}

}