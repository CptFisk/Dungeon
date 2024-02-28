#include <player/player.hpp>

namespace Player {
Player::Player(const Common::typeScale& scale)
  : mPlayerPosition(400, 400, 16.0f * scale.ScaleX, 16.0f * scale.ScaleY)
  , pCurrentTexture(nullptr)
  , pCurrentViewport(nullptr)
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
    return &pCurrentTexture;
}

SDL_FRect**
Player::getPlayerViewport() {
    return &pCurrentViewport;
}

void
Player::addAnimatedTexture(Objects::ObjectAction action, Directions direction, Graphics::AnimatedTexture* texture) {
    mTextures[{ action, direction }] = texture;
    if (pCurrentTexture == nullptr || pCurrentViewport == nullptr) {
        pCurrentTexture  = texture->mTexture;
        pCurrentViewport = texture->getViewport();
    }
}

void
Player::updateReferences() {
    pCurrentTexture  = mTextures[{ mAction, mDirection }]->getTexture();
    pCurrentViewport = mTextures[{ mAction, mDirection }]->getViewport();
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