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
            const std::string& name,
            const std::optional<std::unordered_map<std::string, std::any>>& defaults = std::nullopt);
    ~BeanMan() override;

    [[nodiscard]] BaseMonster* spawn(const float& x, const float& y) const override;
    void                       attack() override;

  protected:
  private:
    const float mMonsterWidth;
    const float mMonsterHeight;


    std::function<bool(const SDL_FPoint&, const double& angle, int& delay)> fcProjectiles;
};

}