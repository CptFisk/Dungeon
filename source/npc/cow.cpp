#include <npc/cow.hpp>

namespace NPC {
Cow::Cow(std::function<bool(const SDL_FPoint&, const float&, const float&)> checkWalls)
  : BaseNPC(26,24,checkWalls) {}

Cow::~Cow() = default;

BaseNPC*
Cow::spawn(const float& x, const float& y) const{
    const auto xPos = x * 16.0f;
    const auto yPos = y * 16.0f;
    auto obj = new Cow(*this);
    obj->mNPCPosition.x = xPos + (16 - mNPCWidth) / 2.0f;
    obj->mNPCPosition.y = yPos + (16 - mNPCHeight) / 2.0f;
    obj->mNPCPosition.w = mNPCWidth;
    obj->mNPCPosition.h = mNPCHeight;
    obj->mNPCCenter.x = xPos + (mNPCWidth / 2.0f);
    obj->mNPCCenter.y = xPos + (mNPCHeight / 2.0f);
    return obj;
}

void
Cow::interact() {
    updateReferences();
}
}