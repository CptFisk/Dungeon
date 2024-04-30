#include <player/player.hpp>

namespace Player {
Player::Player()
  : mTexturePosition{ 0.0f, 0.0f, 16.0f, 16.0f }
  , mInteraction(0.0f, 0.0f, 16.0f, 16.0f)
  , mPlayerCenter{}
  , mCurrentTexture(nullptr)
  , mCurrentViewport(nullptr)
  , mAction(Objects::IDLE)
  , mDirection(SOUTH)
  , mMomentum(0.0f) {}

Player::~Player() = default;

void
Player::spawn(const int& x, const int& y, const Directions& direction) {
    const float _x = static_cast<float>(x) * 16.0f;
    const float _y = static_cast<float>(y) * 16.0f;

    mTexturePosition.x = _x;
    mTexturePosition.y = _y;
    mPlayerCenter.x    = _x + 8.0f; // Offset to make dot in center of player
    mPlayerCenter.y    = _y + 8.0f; // Offset to make dot in center of player
    updatePosition(x, y, direction);
    mDirection = direction;
}

SDL_FRect*
Player::getTexturePosition() {
    return &mTexturePosition;
}

SDL_FPoint*
Player::getPlayerCenter() {
    return &mPlayerCenter;
}

SDL_FRect*
Player::getInteractionArea() {
    return &mInteraction;
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
Player::updatePosition(const float& x, const float& y, const Directions& direction) {
    mTexturePosition.x += x;
    mTexturePosition.y += y;
    mPlayerCenter.x += x;
    mPlayerCenter.y += y;

    switch (direction) {
        case NORTH:
            // Move the interaction box to our top
            mInteraction.x = mTexturePosition.x;
            mInteraction.y = mTexturePosition.y - 16.0f;
            break;
        case EAST:
            // Move the interaction box to our right
            mInteraction.x = mTexturePosition.x + 16.0f;
            mInteraction.y = mTexturePosition.y;
            break;
        case SOUTH:
            // Move the interaction box to our bottom
            mInteraction.x = mTexturePosition.x;
            mInteraction.y = mTexturePosition.y + 16.0f;
            break;
        case WEST:
            // Move the interaction box to our left
            mInteraction.x = mTexturePosition.x - 16.0f;
            mInteraction.y = mTexturePosition.y;
            break;
        default:
            break;
    }
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
    mMomentum = 1.0f;
    switch (direction) {
        case NORTH:
            updatePosition(0.0f, -mMomentum, NORTH);
            break;
        case EAST:
            updatePosition(mMomentum, 0.0f, EAST);
            break;
        case SOUTH:
            updatePosition(0.0f, mMomentum, SOUTH);
            break;
        case WEST:
            updatePosition(-mMomentum, 0.0f, WEST);
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