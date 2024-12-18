#pragma once
#include <monster/monster.hpp>
#include <random>

namespace Monster {
class CaveCrawler : public BaseMonster {
  public:
    CaveCrawler(const int&                                               health,
                const float&                                             velocity,
                const std::string&                                       name,
                const std::optional<std::unordered_map<std::string, std::any>>& defaults = std::nullopt);
    ~CaveCrawler() override;

    [[nodiscard]] BaseMonster* spawn(const float& x, const float& y) const override;
    void                       attack() override;

  protected:
  private:
    const float MONSTER_WIDTH  = 18.0f;
    const float MONSTER_HEIGHT = 18.0f;
};

}