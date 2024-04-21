#pragma once
#include <SDL3/SDL.h>
#include <global.hpp>
#include <graphics/animatedTexture.hpp>
#include <map>
#include <objects/objects.hpp>
#include <utility>
#include <common/structures.hpp>

namespace Player {
class Player {
  public:
    Player();
    ~Player();

    SDL_Texture** getTexture();
    SDL_FRect**   getTextureViewport();
    SDL_FRect*    getTexturePosition();

    void addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture);

    void setAction(Objects::State action);
    void setDirection(Directions direction);
    void resetMomentum();

    float move(Directions direction);

  private:
    Objects::State        mAction; // What are we doing
    Directions            mDirection; // The direction we are facing
    void                  updateReferences();

  protected:
    std::map<std::pair<Objects::State, Directions>, Graphics::AnimatedTexture*> mTextures;

    float mMomentum;
    // Pointer that SDL_Render refer to
    SDL_FRect    mTexturePosition;
    SDL_Texture* mCurrentTexture;
    SDL_FRect*   mCurrentViewport;
};
}