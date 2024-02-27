#pragma once
#include <SDL3/SDL.h>
#include <common/scale.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/structures.hpp>

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
    Health(bool&                       visible,
           int&                        health,
           SDL_Renderer*               renderer,
           Common::typeScale&          scale,
           Graphics::AnimatedTexture*  texture,
           const Graphics::typeSimpleTexture& numbers);
    void draw();

  protected:
  private:
    const SDL_FRect    mPositionHeart;     // Position of heart icon
    const SDL_FRect    mPositionNumber[3]; // Position for numbers
    bool&              mVisible;           // If the UI should be visible
    int&               mHealth;            // Players current health
    Common::typeScale& mScale;             // Game scale

    Graphics::AnimatedTexture*   pHeartTexture; // Texture for the heart icon
    Graphics::typeSimpleTexture mNumbers;      // Textures for numbers

    SDL_Renderer* pRenderer; // Reference to renderer
};
}