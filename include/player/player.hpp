#pragma once
#include <SDL3/SDL.h>
#include <common/structures.hpp>
#include <global.hpp>
#include <graphics/animatedTexture.hpp>
#include <map>
#include <objects/objects.hpp>
#include <utility>

namespace Player {
class Player {
  public:
    Player();
    ~Player();

    SDL_Texture** getTexture();
    SDL_FRect**   getTextureViewport();
    SDL_FRect*    getTexturePosition();
    SDL_FPoint*   getPlayerCenter();
    SDL_FRect*    getInteractionArea();
    /**
     * @brief Move the player to a specific grid coordinate
     * @param x X-coordinate
     * @param y Y-Coordinate
     */
    void spawn(const int& x, const int& y, const Directions& direction = Directions::NORTH);
    void addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture);

    void setAction(Objects::State action);
    void setDirection(Directions direction);
    void resetMomentum();

    float move(Directions direction);

  private:
    Objects::State mAction;    // What are we doing
    Directions     mDirection; // The direction we are facing
    void           updateReferences();
    void           updatePosition(const float& x, const float& y, const Directions& direction); // Update all data related to positioning

  protected:
    std::map<std::pair<Objects::State, Directions>, Graphics::AnimatedTexture*> mTextures;

    float mMomentum;
    // Pointer that SDL_Render refer to
    SDL_FRect    mTexturePosition;
    SDL_Texture* mCurrentTexture;
    SDL_FRect*   mCurrentViewport;
    SDL_FPoint   mPlayerCenter;
    SDL_FRect    mInteraction; // Small box in front of the player that is used to determine if we interact with a object
};
}