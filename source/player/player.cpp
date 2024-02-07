#include <player/player.hpp>

namespace Player {
Player::Player(const float& scaleX, const float& scaleY)
  : mPlayerPosition(100, 100, 16.0 * scaleX, 16.0 * scaleY)
  , mCurrentTexture(nullptr)
  , mCurrentViewport(nullptr)
  , mAction(Objects::Moving)
  , mDirection(South)
  , mMomentum(0.0) {}

Player::~Player() {}

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
Player::updateAnimation() {
    for (auto& texture : mTextures) {
        texture.second->nextViewport();
    }
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
        case North:
            mPlayerPosition.y -= 3;
            break;
        case East:
            mPlayerPosition.x += 3;
            break;
        case South:
            mPlayerPosition.y += 3;
            break;
        case West:
            mPlayerPosition.x -= 3;
            break;
    }
    mAction    = Objects::Moving;
    mDirection = direction;
    updateReferences();
}

}