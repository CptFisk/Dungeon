#pragma once
#include <SDL.h>
#include <common/coordinates.hpp>
#include <global.hpp>
#include <graphics/types/animatedTexture.hpp>
#include <map>
#include <object/objects.hpp>
#include <utility>

namespace Player {
class Player {
  public:
    Player();
    ~Player();

    SDL_Texture**           getTexture();
    SDL_Rect**              getTextureViewport();
    SDL_FRect*              getTexturePosition();
    SDL_FPoint&             getPlayerCenter();
    [[nodiscard]] SDL_Point getPlayerCoordinates() const;
    SDL_FRect*              getInteractionArea();
    /**
     * @brief Move the player to a specific grid coordinate
     * @param x X-coordinate
     * @param y Y-Coordinate
     */
    void spawn(const uint8_t& x, const uint8_t& y, const Orientation& direction = Orientation::North);
    void spawn(const std::pair<uint8_t, uint8_t>& pos, const Orientation& direction = Orientation::North);
    void spawn(const Common::type2DMapCoordinate& pos, const Orientation& direction = Orientation::North);

    void addAnimatedTexture(Objects::State action, Orientation direction, Graphics::AnimatedTexture* texture);

    void setAction(Objects::State action);
    void setDirection(Orientation direction);
    void resetMomentum();

    void move(const SDL_FPoint& vector);
  private:
    Objects::State mAction;    // What are we doing
    Orientation    mDirection; // The direction we are facing
    void           updateReferences();
    void           updateInteraction();                                                         // Update interaction box
    void           updatePosition(const float& x, const float& y, const Orientation& direction); // Update all data related to positioning

  protected:
    std::map<std::pair<Objects::State, Orientation>, Graphics::AnimatedTexture*> mTextures;

    float mMomentum;
    // Pointer that SDL_Render refer to
    SDL_FRect    mTexturePosition;
    SDL_Texture* mCurrentTexture;
    SDL_Rect*    mCurrentViewport;
    SDL_FPoint   mPlayerCenter;
    /**
     * @brief Small box that is used as a interaction area for opening doors, talk to npc and also melee attacks.
     * @details The box is of dimensions:
     * @details North/South: 8 height 12 width
     * @details East/West: 18 height 8 width
     */
    SDL_FRect    mInteraction;
};
}