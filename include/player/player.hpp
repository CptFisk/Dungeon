#pragma once
#include <SDL3/SDL.h>
#include <global.hpp>
#include <graphics/animatedTexture.hpp>
#include <map>
#include <objects/objects.hpp>
#include <utility>
#include <engine/structures.hpp>

namespace Player {
class Player {
  public:
    Player(const Engine::Scale& scale);
    ~Player();

    SDL_Texture** getPlayerTexture();
    SDL_FRect**   getPlayerViewport();
    SDL_FRect*    getPlayerPosition();

    void addAnimatedTexture(Objects::ObjectAction action, Directions direction, Graphics::AnimatedTexture* texture);

    void setAction(Objects::ObjectAction action);
    void setDirection(Directions direction);

    void move(Directions direction);

  private:
    Objects::ObjectAction mAction; // What are we doing
    Directions            mDirection; // The direction we are facing
    void                  updateReferences();

  protected:
    std::map<std::pair<Objects::ObjectAction, Directions>, Graphics::AnimatedTexture*> mTextures;

    float mMomentum;
    // Pointer that SDL_Render refer to
    SDL_FRect    mPlayerPosition;
    SDL_Texture* mCurrentTexture;
    SDL_FRect*   mCurrentViewport;
};
}