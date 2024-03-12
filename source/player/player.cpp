#include <player/player.hpp>

namespace Player {
Player::Player()
  : mPlayerPosition(16.0f, 16.0f, 16.0f, 16.0f)
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
Player::addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture) {
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
Player::setAction(Objects::State action) {
    mAction = action;
    updateReferences();
}

void
Player::setDirection(Directions direction) {
    mDirection = direction;
    updateReferences();
}

float
Player::move(Directions direction) {
    switch (direction) {
        case NORTH:
            mPlayerPosition.y -= 0.5f;
            break;
        case EAST:
            mPlayerPosition.x += 0.5f;
            break;
        case SOUTH:
            mPlayerPosition.y += 0.5f;
            break;
        case WEST:
            mPlayerPosition.x -= 0.5f;
            break;
        case ALL:
        default:
            break;
    }
    mAction    = Objects::MOVE;
    mDirection = direction;
    updateReferences();
    return 0.5f;
}

}