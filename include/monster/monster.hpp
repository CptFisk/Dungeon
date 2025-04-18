#pragma once
#include <any>
#include <global.hpp>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/drawData.hpp>
#include <optional>
#include <unordered_map>

namespace Monster {

class BaseMonster {
  public:
    BaseMonster(const int&                                                      health,
                const float&                                                    velocity,
                const int&                                                      experience,
                const std::string&                                              lua,
                const std::optional<std::unordered_map<std::string, std::any>>& defaults = std::nullopt);
    BaseMonster(const BaseMonster& other);
    virtual ~BaseMonster();

    [[nodiscard]] virtual BaseMonster* spawn(const float& x, const float& y) const = 0;
    /**
     * @brief Deal damage to the monster.
     * @param damage
     */

    void                setPlayerDistance(const float& dist);
    [[nodiscard]] float getPlayerDistance() const;
    [[nodiscard]] int   getExperience() const;

    /**
     * @brief Damage the monster
     * @param damage Damage to apply
     * @return Return true if the blow was fatal
     */
    bool damageMonster(const int& damage);
    /**
     * @brief Return the status of mInflictDamage
     * @return True means that the monster can hurt you
     */
    [[maybe_unused]] [[nodiscard]] bool inflictDamage() const;
    [[nodiscard]] std::string           getLuaFile() const;

    void addAnimatedTexture(Objects::State action, Orientation direction, Graphics::AnimatedTexture* texture);

    [[maybe_unused]] void setState(Objects::State state);
    [[maybe_unused]] void setDirection(Orientation direction);

    Graphics::typeDrawData getMonster();
    /**
     * @brief Returns the monster position in top left corner as SDL_FRect
     */
    SDL_FRect* getPosition();
    /**
     * @brief Set position of the monster, the position is referred to as the center point
     * @param x X-Position
     * @param y Y-Position
     */
    void setPosition(const float& x, const float& y);
    /**
     * @brief Move the monster from the original position, that number of values in x,y
     * @param x
     * @param y
     */
    void movePosition(const float& x, const float& y);
    /**
     * @brief Moves the monster in a specific angle with its base velocity (if not specified)
     * @param angle Angle used in movement
     * @optional Velocity
     */
    void moveAngle(const double& angle, std::optional<float> velocity);
    /**
     * @brief Returns the monsters velocity
     */
    float getVelocity() const;
    /**
     * @brief Return the monster center position
     * @return
     */
    SDL_FPoint getCenter() const;
    /**
     * @brief Return the monsters current state
     */
    Objects::State getState();
    /**
     * @brief Returns a retained parameter from memory.
     * @param param Name of parameter
     * @return
     */
    [[nodiscard]] std::optional<std::any> getRetain(const std::string& param);
    /**
     * @brief Set a value for a parameter into retain memory. This can later be retried
     * @param param Key name
     * @param value Value to be stored
     */
    void setRetain(const std::string& param, const std::any& value);
    /**
     * @brief Virtual function used to do special attack patterns
     */
    virtual void attack() = 0;

  private:
  protected:
    std::string luaFile; // Name of the lua file that will be executed
    const float mVelocity;
    int         mTicks;
    const int   DEATH_ANIMATION = 30;

    bool mInflictDamage; // Monster can inflict damage
    int  mHealth;        // Monster health
    int  mExperience;    // Reward for killing the beast

    Objects::State mState;     // What are we doing
    Orientation    mDirection; // The direction we are facing

    std::map<std::pair<Objects::State, Orientation>, Graphics::AnimatedTexture*> mTextures;

    // Pointer that SDL_Render refer to
    SDL_FPoint   mMonsterCenter;   // Center of the monster
    SDL_FRect    mMonsterPosition; // Drawing area of the monster
    SDL_Texture* pCurrentTexture;  // Reference to the current texture
    SDL_Rect*    pCurrentViewport; // Reference to the current viewport

    float mPlayerDistance; // Distance to the player

    void updateReferences();

    // Memory functions for lua interface
    std::unordered_map<std::string, std::any> mRetains;
};
}