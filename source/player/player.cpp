#include <player/player.hpp>

namespace Player {
Player::Player(const Common::typeScale& scale)
  : mPlayerPosition(400, 400, 16.0f * scale.ScaleX, 16.0f * scale.ScaleY)
  , mCurrentTexture(nullptr)
  , mCurrentViewport(nullptr)
  , mAction(Objects::IDLE)
  , mDirection(SOUTH)
  , mMomentum(0.0) {}

Player::~Player() = default;

SDL_FRect*
Player::getPlayerPosition() {
    return &mPlayerPosition;
}

SDL_Texture**
Player::getPlayerTexture() {
    return &mCurrentTexture;
}

SDL_FRect**
Player::getPlayerViewport() {
    return &mCurrentViewport;
}

void
Player::addAnimatedTexture(Objects::ObjectAction action, Directions direction, Graphics::AnimatedTexture* texture) {
    mTextures[{ action, direction }] = texture;
    if (mCurrentTexture == nullptr || mCurrentViewport == nullptr) {
        mCurrentTexture  = texture->mTexture;
        mCurrentViewport = texture->getViewport();
    }
}

void
Player::updateReferences() {
    mCurrentTexture  = mTextures[{ mAction, mDirection }]->getTexture();
    mCurrentViewport = mTextures[{ mAction, mDirection }]->getViewport();
}

void
Player::setAction(Objects::ObjectAction action) {
    mAction = action;
    updateReferences();
}

void
Player::setDirection(Directions direction) {
    mDirection = direction;
    updateReferences();
}

void
Player::move(Directions direction) {
    switch (direction) {
        case NORTH:
            mPlayerPosition.y -= 3;
            break;
        case EAST:
            mPlayerPosition.x += 3;
            break;
        case SOUTH:
            mPlayerPosition.y += 3;
            break;
        case WEST:
            mPlayerPosition.x -= 3;
            break;
    }
    mAction    = Objects::MOVE;
    mDirection = direction;
    updateReferences();
}

}