#include <monster/monster.hpp>
#include <utility/trigonometry.hpp>
namespace Monster {
BaseMonster::BaseMonster(const int&                                       health,
                         const float&                                     velocity,
                         const std::string&                               lua,
                         const std::optional<std::unordered_map<std::string, std::any>>& defaults)
  : luaFile(lua + ".lua")
  , mInflictDamage(true)
  , mHealth(health)
  , mVelocity(velocity)
  , mRetains(defaults.value_or(std::unordered_map<std::string, std::any>()))
  , mTicks(0)
  , pCurrentTexture(nullptr)
  , pCurrentViewport(nullptr)
  , mState(Objects::IDLE)
  , mDirection(SOUTH)
  , DEATH_ANIMATION(20) {}

BaseMonster::BaseMonster(const Monster::BaseMonster& other)
  : mHealth(other.mHealth)
  , mVelocity(other.mVelocity)
  , mState(other.mState)
  , mTextures(other.mTextures)
  , mMonsterPosition(other.mMonsterPosition)
  , mMonsterCenter(other.mMonsterCenter)
  , mDirection(SOUTH)
  , mInflictDamage(false)
  , pCurrentTexture(other.pCurrentTexture)
  , pCurrentViewport(other.pCurrentViewport)
  , mTicks(0)
  , DEATH_ANIMATION(20) {}

BaseMonster::~BaseMonster() = default;

void
BaseMonster::setPlayerDistance(const float& dist) {
    mPlayerDistance = dist;
}

float
BaseMonster::getPlayerDistance() const {
    return mPlayerDistance;
}

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
    const auto w  = (mMonsterPosition.w / 2.0f);
    const auto h  = (mMonsterPosition.h / 2.0f);
    auto       _x = x - w;
    auto       _y = y - h;

    mMonsterPosition.x = _x;
    mMonsterPosition.y = _y;
    mMonsterCenter.x   = _x + w;
    mMonsterCenter.y   = _y + h;
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
    const auto& speed    = velocity.has_value() ? velocity.value() : mVelocity;
    const auto  position = Utility::calculateVector(angle, mVelocity);
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
BaseMonster::getCenter() const{
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
    if (mRetains.find(param) != mRetains.end())
        return mRetains[param];
    return std::nullopt;
}

void
BaseMonster::updateReferences() {
    pCurrentTexture  = mTextures[{ mState, mDirection }]->getTexture();
    pCurrentViewport = mTextures[{ mState, mDirection }]->getAnimatedViewport();
}

}