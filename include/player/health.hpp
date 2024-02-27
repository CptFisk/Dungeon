#pragma once
#include <SDL3/SDL.h>
#include <common/scale.hpp>
#include <graphics/animatedTexture.hpp>

namespace Player {
class Health {
  public:
    /**
     * @brief Constructor for health icon and numbers
     * @param visible Shall UI be visible
     * @param health Current health
     * @param renderer Pointer to renderer
     * @param scale Game scale factor
     * @param texture Texture
     */
    Health(bool& visible, int& health, SDL_Renderer* renderer, Common::typeScale& scale, Graphics::AnimatedTexture* texture);
    void draw();

  protected:
  private:
    const SDL_FRect            mPosition;     // Position of heart icon
    bool&                      mVisible;      // If the UI should be visible
    int&                       mHealth;       // Players current health
    Common::typeScale&         mScale;        // Game scale
    Graphics::AnimatedTexture* pHeartTexture; // Texture for the heart icon

    SDL_Renderer* pRenderer;    //Reference to renderer
};
}