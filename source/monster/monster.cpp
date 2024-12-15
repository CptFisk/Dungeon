#include <monster/monster.hpp>
#include <utility/trigonometry.hpp>
namespace Monster {
BaseMonster::BaseMonster(const int&                                                          health,
                         const float&                                                        velocity,
                         const std::string&                                                  lua,
                         SDL_FPoint&                                                         playerCenter,
                         std::function<bool(const SDL_FPoint&, const float&, const float&)>& checkWalls)
  : luaFile(lua + ".lua")
  , mInflictDamage(true)
  , mHealth(health)
  , mVelocity(velocity)
  , mTicks(0)
  , pCurrentTexture(nullptr)
  , pCurrentViewport(nullptr)
  , mPlayerCenter(playerCenter)
  , mState(Objects::IDLE)
  , mDirection(SOUTH)
  , fCheckWalls(checkWalls)
  , DEATH_ANIMATION(20) {}

BaseMonster::BaseMonster(const Monster::BaseMonster& other)
  : mHealth(other.mHealth)
  , mVelocity(other.mVelocity)
  , mState(other.mState)
  , mTextures(other.mTextures)
  , mMonsterPosition(other.mMonsterPosition)
  , mMonsterCenter(other.mMonsterCenter)
  , mDirection(SOUTH)
  , fCheckWalls(other.fCheckWalls)
  , mInflictDamage(false)
  , pCurrentTexture(other.pCurrentTexture)
  , pCurrentViewport(other.pCurrentViewport)
  , mPlayerCenter(other.mPlayerCenter)
  , mTicks(0)
  , DEATH_ANIMATION(20) {}

BaseMonster::~BaseMonster() = default;

void
BaseMonster::damageMonster(const int& damage) {
    mHealth -= damage;
    if (mHealth < 0) {
        mState = Objects::DYING;
        updateReferences();
    }
}

bool
BaseMonster::inflictDamage() const {
    return mInflictDamage;
}

std::string
BaseMonster::getLuaFile() const {
    return luaFile;
}

void
BaseMonster::addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture) {
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
BaseMonster::setDirection(Directions direction) {
    mDirection = direction;
    updateReferences();
}

void
BaseMonster::setPosition(const float& x, const float& y) {
    auto _x            = x - (mMonsterPosition.w / 2.0f);
    auto _y            = y - (mMonsterPosition.h / 2.0f);
    mMonsterPosition.x = _x;
    mMonsterPosition.y = _y;
    mMonsterCenter.x   = _x;
    mMonsterCenter.y   = _y;
}

void
BaseMonster::movePosition(const float& x, const float& y) {
    mMonsterPosition.x += x;
    mMonsterPosition.y += y;
    mMonsterCenter.x += x;
    mMonsterCenter.y += y;
}

void
BaseMonster::moveAngle(const double& angle, std::optional<float> velocity) {
    const auto& speed = velocity.has_value() ? velocity.value() : mVelocity;
    const auto position = Utility::calculateVector(angle, mVelocity);
    movePosition(position.x, position.y);
}

float
BaseMonster::getVelocity() const {
    return mVelocity;
}

Graphics::typeDrawData
BaseMonster::getMonster() {
    return Graphics::typeDrawData{ pCurrentTexture, pCurrentViewport, &mMonsterPosition };
}

SDL_FRect*
BaseMonster::getPosition() {
    return &mMonsterPosition;
}

SDL_FPoint
BaseMonster::getCenter() {
    return mMonsterCenter;
}

[[maybe_unused]] void
BaseMonster::setState(Objects::State state) {
    mState = state;
    updateReferences();
}

Objects::State
BaseMonster::getState() {
    if (mState == Objects::DYING) {
        if (mTicks++ > DEATH_ANIMATION)
            mState = Objects::DEAD;
    }
    return mState;
}

void
BaseMonster::setRetain(const std::string& param, const std::any& value) {
    mRetains[param] = value;
}

std::optional<std::any>
BaseMonster::getRetain(const std::string& param) {
    if(mRetains.find(param) != mRetains.end())
        return mRetains[param];
    return std::nullopt;
}


void
BaseMonster::updateReferences() {
    pCurrentTexture  = mTextures[{ mState, mDirection }]->getTexture();
    pCurrentViewport = mTextures[{ mState, mDirection }]->getAnimatedViewport();
}

}