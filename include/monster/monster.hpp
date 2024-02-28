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
    BaseMonster(const int& health, const float& velocity);
    BaseMonster(const BaseMonster& other);
    ~BaseMonster();

    BaseMonster* spawn() const;

    bool damage(const int& damage);

    void addAnimatedTexture(Objects::ObjectAction action, Directions direction, Graphics::AnimatedTexture* texture);

    void setAction(Objects::ObjectAction action);
    void setDirection(Directions direction);

    typeMonsterData getMonster();

  protected:
  private:
    const float mVelocity;
    int         mHealth; // Monster health

    Objects::ObjectAction mAction;    // What are we doing
    Directions            mDirection; // The direction we are facing

    std::map<std::pair<Objects::ObjectAction, Directions>, Graphics::AnimatedTexture*> mTextures;

    // Pointer that SDL_Render refer to
    SDL_FRect    mMonsterPosition;
    SDL_Texture* pCurrentTexture;
    SDL_FRect*   pCurrentViewport;

    void updateReferences();
};
}