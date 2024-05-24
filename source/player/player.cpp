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
Player::spawn(const std::pair<uint8_t, uint8_t>& pos, const Directions& direction) {
    spawn(pos.first, pos.second, direction);
}

void
Player::spawn(const uint8_t& x, const uint8_t& y, const Directions& direction) {
    const float _x = std::max((static_cast<float>(x) * 16.0f), 0.0f); // We reduce by 16 because position is top left corner
    const float _y = std::max((static_cast<float>(y) * 16.0f), 0.0f);

    mTexturePosition.x = _x;
    mTexturePosition.y = _y;
    mPlayerCenter.x    = _x + 8.0f; // Offset to make dot in center of player
    mPlayerCenter.y    = _y + 8.0f; // Offset to make dot in center of player
    mDirection         = direction;
    updateInteraction();
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

SDL_Rect**
Player::getTextureViewport() {
    return &mCurrentViewport;
}

void
Player::addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture) {
    mTextures[{ action, direction }] = texture;
    if (mCurrentTexture == nullptr || mCurrentViewport == nullptr) {
        mCurrentTexture  = texture->getTexture();
        mCurrentViewport = texture->getViewport();
    }
}

void
Player::updateReferences() {
    mCurrentTexture  = mTextures[{ mAction, mDirection }]->getTexture();
    mCurrentViewport = mTextures[{ mAction, mDirection }]->getViewport();
}

void
Player::updateInteraction() {
    switch (mDirection) {
        case NORTH:
            // Move the interaction box to our top
            mInteraction.x = mTexturePosition.x;
            mInteraction.y = mTexturePosition.y - 8.0f;
            mInteraction.h = 8.0f;
            mInteraction.w = 16.0f;
            break;
        case EAST:
            // Move the interaction box to our right
            mInteraction.x = mTexturePosition.x + 16.0f;
            mInteraction.y = mTexturePosition.y;
            mInteraction.h = 16.0f;
            mInteraction.w = 8.0f;
            break;
        case SOUTH:
            // Move the interaction box to our bottom
            mInteraction.x = mTexturePosition.x;
            mInteraction.y = mTexturePosition.y + 16.0f;
            mInteraction.h = 8.0f;
            mInteraction.w = 16.0f;
            break;
        case WEST:
            // Move the interaction box to our left
            mInteraction.x = mTexturePosition.x - 8.0f;
            mInteraction.y = mTexturePosition.y;
            mInteraction.h = 16.0f;
            mInteraction.w = 8.0f;
            break;
        default:
            break;
    }
}

void
Player::updatePosition(const float& x, const float& y, const Directions& direction) {
    mTexturePosition.x += x;
    mTexturePosition.y += y;
    mPlayerCenter.x += x;
    mPlayerCenter.y += y;
    mDirection = direction;
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
    updateInteraction();
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
    updateInteraction();
    return mMomentum;
}

}