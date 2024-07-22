#pragma once
#include <SDL.h>
#include <common/structures.hpp>
#include <global.hpp>
#include <graphics/animatedTexture.hpp>
#include <map>
#include <object/objects.hpp>
#include <level/types/coordinate.hpp>
#include <utility>

namespace Player {
class Player {
  public:
    Player();
    ~Player();

    SDL_Texture** getTexture();
    SDL_Rect**    getTextureViewport();
    SDL_FRect*    getTexturePosition();
    SDL_FPoint&   getPlayerCenter();
    SDL_FRect*    getInteractionArea();
    /**
     * @brief Move the player to a specific grid coordinate
     * @param x X-coordinate
     * @param y Y-Coordinate
     */
    void spawn(const uint8_t& x, const uint8_t& y, const Directions& direction = Directions::NORTH);
    void spawn(const std::pair<uint8_t, uint8_t>& pos, const Directions& direction = Directions::NORTH);
    void spawn(const Level::type2DMapCoordinate& pos, const Directions& direction = Directions::NORTH);

    void addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture);

    void setAction(Objects::State action);
    void setDirection(Directions direction);
    void resetMomentum();

    float move(Directions direction);

  private:
    Objects::State mAction;    // What are we doing
    Directions     mDirection; // The direction we are facing
    void           updateReferences();
    void           updateInteraction();                                                         // Update interaction box
    void           updatePosition(const float& x, const float& y, const Directions& direction); // Update all data related to positioning

  protected:
    std::map<std::pair<Objects::State, Directions>, Graphics::AnimatedTexture*> mTextures;

    float mMomentum;
    // Pointer that SDL_Render refer to
    SDL_FRect    mTexturePosition;
    SDL_Texture* mCurrentTexture;
    SDL_Rect*    mCurrentViewport;
    SDL_FPoint   mPlayerCenter;
    SDL_FRect    mInteraction; // Small box in front of the player that is used to determine if we interact with a object
};
}