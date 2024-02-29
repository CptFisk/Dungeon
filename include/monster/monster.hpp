#pragma once
#include <common/structures.hpp>
#include <global.hpp>
#include <graphics/animatedTexture.hpp>

namespace Monster {

struct typeMonsterData {
    SDL_Texture* Texture;
    SDL_FRect*   Viewport;
    SDL_FRect*   Position;
};

class BaseMonster {
  public:
    BaseMonster(const int& health, const float& velocity, SDL_FRect* playerPosition);
    BaseMonster(const BaseMonster& other);
    ~BaseMonster();

    virtual BaseMonster* spawn(const float& x, const float& y) const = 0;
    /**
     * @brief Deal damage to the monster.
     * @param damage
     */
    void damageMonster(const int& damage);
    /**
     * @brief Return the status of mInflictDamage
     * @return True means that the monster can hurt you
     */
    bool inflictDamage() const;

    void addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture);

    void setAction(Objects::State action);
    void setDirection(Directions direction);

    virtual void interact() = 0;

    typeMonsterData getMonster();

  private:
  protected:
    bool        mInflictDamage;    //Monster can inflict damage
    const float mVelocity;
    int         mHealth; // Monster health

    Objects::State        mAction;    // What are we doing
    Directions            mDirection; // The direction we are facing

    std::map<std::pair<Objects::State, Directions>, Graphics::AnimatedTexture*> mTextures;

    // Pointer that SDL_Render refer to
    SDL_FRect    mMonsterPosition;
    SDL_Texture* pCurrentTexture;
    SDL_FRect*   pCurrentViewport;
    SDL_FRect*   pPlayerPosition;

    void updateReferences();
};
}