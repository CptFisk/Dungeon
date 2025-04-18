#pragma once
#include <monster/monster.hpp>

namespace Monster {
/**
 * @brief Base class for all small slimes that exist.
 */
class Slime : public BaseMonster {
  public:
    Slime(const int&                                                      health,
          const float&                                                    velocity,
          const int&                                                      experience,
          const std::string&                                              name,
          const std::optional<std::unordered_map<std::string, std::any>>& defaults = std::nullopt);
    ~Slime();

    [[nodiscard]] BaseMonster* spawn(const float& x, const float& y) const override;
    void                       attack() override;

  protected:
  private:
    const float MONSTER_WIDTH  = 12.0f;
    const float MONSTER_HEIGHT = 10.0f;
};

}