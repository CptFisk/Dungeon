#pragma once
#include <SDL.h>
#include <graphics/types/baseTexture.hpp>
#include <vector>

namespace Graphics {
class LightningTexture : public BaseTexture {
  public:
    LightningTexture(SDL_Texture* texture, const int& w, const int& h, const int& ticks, const int& alpha);
    ~LightningTexture();
    /**
     * @brief Return the current Lightning viewport
     * @return SDL_Rect*
     */
    [[nodiscard]] SDL_Rect* getAnimatedViewport();
    /**
     * @brief Shall be called after all the viewports is added to finish the process
     */
    void addViewportDone();
    /**
     * @brief Update the animation frame for the texture
     */
    void               updateTexture();
    [[nodiscard]] bool done() const;     // Animation is last frame
    [[nodiscard]] int  getTicks() const; // Return the maximum number of ticks

  private:
  protected:
    int       mView; // Selector for viewports
    int       mCycles;
    const int mTicks;
    int       mCurrentTicks;
    SDL_Rect  mCurrentViewport;
};
}