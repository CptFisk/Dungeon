#pragma once
#include <npc/npc.hpp>

namespace NPC {

class Cow : public BaseNPC{
  public:
    Cow(std::function<bool(const SDL_FPoint&, const float&, const float&)> checkWalls);
    ~Cow();

    [[nodiscard]]BaseNPC* spawn(const float& x, const float& y) const override;
    void interact() override;

};

}