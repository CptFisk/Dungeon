#pragma once
#include <global.hpp>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/drawData.hpp>

namespace NPC {

class BaseNPC {
  public:
    BaseNPC(const float& width, const float& height, std::function<bool(const SDL_FPoint&, const float&, const float&)>& checkWalls);
    BaseNPC(const BaseNPC& other);
    virtual ~BaseNPC();

    [[nodiscard]] virtual BaseNPC* spawn(const float& x, const float& y) const = 0;

    void addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture);

    [[maybe_unused]] void setAction(Objects::State action);
    [[maybe_unused]] void setDirection(Directions direction);
    void                  updatePosition(const float& x, const float& y);

    virtual void interact() = 0;

    Graphics::typeDrawData getNpc();
    SDL_FRect*             getPosition();
    Objects::State         getState();

  private:
  protected:
    const float mVelocity;
    const float mNPCWidth;
    const float mNPCHeight;

    Objects::State mState;     // What are we doing
    Directions     mDirection; // The direction we are facing

    std::map<std::pair<Objects::State, Directions>, Graphics::AnimatedTexture*> mTextures;

    // Pointer that SDL_Render refer to
    SDL_FPoint   mNPCCenter;       // Center of the monster
    SDL_FRect    mNPCPosition;     // Drawing area of the monster
    SDL_Texture* pCurrentTexture;  // Reference to the current texture
    SDL_Rect*    pCurrentViewport; // Reference to the current viewport

    void updateReferences();

    // Global help functions
    std::function<bool(const SDL_FPoint&, const float&, const float&)> fCheckWalls;
};
}