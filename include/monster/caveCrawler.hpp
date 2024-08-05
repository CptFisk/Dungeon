#pragma once
#include <monster/monster.hpp>
#include <random>

namespace Monster {
class CaveCrawler : public BaseMonster {
  public:
    CaveCrawler(const int&                                                            health,
                const float&                                                          velocity,
                SDL_FPoint&                                                           playerCenter,
                std::function<bool(const SDL_FPoint&, const float&, const float&)> checkWalls);
    ~CaveCrawler() override;

    [[nodiscard]] BaseMonster* spawn(const float& x, const float& y) const override;
    void         interact() override;

  protected:
  private:
    const float MONSTER_WIDTH  = 18.0f;
    const float MONSTER_HEIGHT = 18.0f;
};

}