#include <player/player.hpp>
#include <error.hpp>
namespace Player {
Player::Player()
  : mTexturePosition{ 0.0f, 0.0f, 12.0f, 18.0f }
  , mInteraction({ 0.0f, 0.0f, 19.0f, 9.0f })
  , mPlayerCenter{}
  , mCurrentTexture(nullptr)
  , mCurrentViewport(nullptr)
  , mAction(Objects::IDLE)
  , mDirection(South)
  , mMomentum(0.0f) {}

Player::~Player() = default;

void
Player::spawn(const std::pair<uint8_t, uint8_t>& pos, const Orientation& orientation) {
    spawn(pos.first, pos.second, orientation);
}

void
Player::spawn(const Common::type2DMapCoordinate& pos, const Orientation& orientation) {
    spawn(pos.X, pos.Y, orientation);
}

void
Player::spawn(const uint8_t& x, const uint8_t& y, const Orientation& orientation) {
    const float _x = std::max((static_cast<float>(x) * 16.0f), 0.0f); // We reduce by 16 because position is top left corner
    const float _y = std::max((static_cast<float>(y) * 16.0f), 0.0f);

    mTexturePosition.x = _x;
    mTexturePosition.y = _y;
    mPlayerCenter.x    = _x + 6.0f; // Offset to make dot in center of player
    mPlayerCenter.y    = _y + 8.5f; // Offset to make dot in center of player
    mDirection         = orientation;
    updateInteraction();
}

SDL_FRect*
Player::getTexturePosition() {
    return &mTexturePosition;
}

SDL_FPoint&
Player::getPlayerCenter() {
    return mPlayerCenter;
}

SDL_Point
Player::getPlayerCoordinates() const {
    return { INT(mPlayerCenter.x / 16), INT(mPlayerCenter.y / 16) };
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
Player::addAnimatedTexture(Objects::State action, Orientation orientation, Graphics::AnimatedTexture* texture) {
    ASSERT_WITH_MESSAGE(mTextures.find({action, orientation}) != mTextures.end(), "Texture already loaded");
    mTextures[{ action, orientation }] = texture;
    if (mCurrentTexture == nullptr || mCurrentViewport == nullptr) {
        mCurrentTexture  = texture->getTexture();
        mCurrentViewport = texture->getAnimatedViewport();
    }
}

void
Player::addSweepTexture(const Orientation& orientation, Graphics::AnimatedTexture* texture) {
    ASSERT_WITH_MESSAGE(mSweeps.find(orientation) != mSweeps.end(), "Texture already loaded");
    mSweeps[orientation] = texture;
}

void
Player::updateReferences() {
    mCurrentTexture  = mTextures[{ mAction, mDirection }]->getTexture();
    mCurrentViewport = mTextures[{ mAction, mDirection }]->getAnimatedViewport();
}

void
Player::updateInteraction() {
    switch (mDirection) {
        case North:
            // Move the interaction box to our top
            mInteraction.x = mTexturePosition.x - 4.0f;
            mInteraction.y = mTexturePosition.y - 9.0f;
            mInteraction.h = 9.0f;
            mInteraction.w = 19.0f;
            break;
        case East:
            // Move the interaction box to our right
            mInteraction.x = mTexturePosition.x + 12.0f;
            mInteraction.y = mTexturePosition.y;
            mInteraction.h = 19.0f;
            mInteraction.w = 9.0f;
            break;
        case South:
            // Move the interaction box to our bottom
            mInteraction.x = mTexturePosition.x - 4.0f;
            mInteraction.y = mTexturePosition.y + 18.0f;
            mInteraction.h = 9.0f;
            mInteraction.w = 19.0f;
            break;
        case West:
            // Move the interaction box to our left
            mInteraction.x = mTexturePosition.x - 9.0f;
            mInteraction.y = mTexturePosition.y;
            mInteraction.h = 19.0f;
            mInteraction.w = 9.0f;
            break;
        default:
            break;
    }
}

void
Player::updatePosition(const float& x, const float& y, const Orientation& direction) {
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
Player::setDirection(Orientation direction) {
    mDirection = direction;
    updateReferences();
    updateInteraction();
}

void
Player::resetMomentum() {
    mMomentum = 0.1f;
}

void
Player::move(const SDL_FPoint& vector, const Orientation& orientation) {
    updatePosition(vector.x, vector.y, orientation);
    mAction    = Objects::MOVE;
    mDirection = orientation;
    updateReferences();
    updateInteraction();
}

}