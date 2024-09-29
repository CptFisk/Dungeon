#pragma once
#include <monster/monster.hpp>
#include <random>

namespace Monster {
class BeanMan : public BaseMonster {
  public:
    BeanMan(const float&                                                            width,
            const float&                                                            height,
            const int&                                                              health,
            const float&                                                            velocity,
            SDL_FPoint&                                                             playerCenter,
            std::function<bool(const SDL_FPoint&, const float&, const float&)>      checkWalls,
            std::function<bool(const SDL_FPoint&, const double& angle, int& delay)> projectiles);
    ~BeanMan() override;

    [[nodiscard]] BaseMonster* spawn(const float& x, const float& y) const override;
    void                       interact() override;

  protected:
    // SDL_FPoint wobbleMovement(const double& angle, const float& velocity);
  private:
    const float mMonsterWidth;
    const float mMonsterHeight;

    int mReload;
    int mDelay;     //Used in projectile function

    std::function<bool(const SDL_FPoint&, const double& angle, int& delay)> fcProjectiles;
};

}