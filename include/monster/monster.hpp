#pragma once
#include <global.hpp>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/drawData.hpp>

namespace Monster {

class BaseMonster {
  public:
    BaseMonster(const int&                                                          health,
                const float&                                                        velocity,
                const std::string&                                                  lua,
                SDL_FPoint&                                                         playerCenter,
                std::function<bool(const SDL_FPoint&, const float&, const float&)>& checkWalls);
    BaseMonster(const BaseMonster& other);
    virtual ~BaseMonster();

    [[nodiscard]] virtual BaseMonster* spawn(const float& x, const float& y) const = 0;
    /**
     * @brief Deal damage to the monster.
     * @param damage
     */
    void damageMonster(const int& damage);
    /**
     * @brief Return the status of mInflictDamage
     * @return True means that the monster can hurt you
     */
    [[maybe_unused]] [[nodiscard]] bool inflictDamage() const;
    [[nodiscard]] std::string           getLuaFile() const;

    void addAnimatedTexture(Objects::State action, Directions direction, Graphics::AnimatedTexture* texture);

    [[maybe_unused]] void setState(Objects::State state);
    [[maybe_unused]] void setDirection(Directions direction);

    virtual void interact() = 0;

    Graphics::typeDrawData getMonster();
    SDL_FRect*             getPosition();
    /**
     * @brief Set position of the monster, the position is referred to as the center point
     * @param x X-Position
     * @param y Y-Position
     */
    void           setPosition(const float& x, const float& y);
    /**
     * @brief Move the monster from the original position, that number of values in x,y
     * @param x
     * @param y
     */
    void           movePosition(const float& x, const float& y);
    SDL_FPoint     getCenter();
    Objects::State getState();

  private:
  protected:
    std::string luaFile; // Name of the lua file that will be executed
    const float mVelocity;
    int         mTicks;
    const int   DEATH_ANIMATION = 30;

    bool mInflictDamage; // Monster can inflict damage
    int  mHealth;        // Monster health

    Objects::State mState;     // What are we doing
    Directions     mDirection; // The direction we are facing

    std::map<std::pair<Objects::State, Directions>, Graphics::AnimatedTexture*> mTextures;

    // Pointer that SDL_Render refer to
    SDL_FPoint   mMonsterCenter;   // Center of the monster
    SDL_FRect    mMonsterPosition; // Drawing area of the monster
    SDL_Texture* pCurrentTexture;  // Reference to the current texture
    SDL_Rect*    pCurrentViewport; // Reference to the current viewport
    SDL_FPoint&  mPlayerCenter;    // Reference to the center of the player (used for targeting etc.)

    void updateReferences();

    // Global help functions
    std::function<bool(const SDL_FPoint&, const float&, const float&)> fCheckWalls;
};
}