#pragma once
#include <SDL.h>
#include <graphics/types/baseTexture.hpp>
#include <vector>

namespace Graphics {
class AnimatedTexture : public BaseTexture {
  public:
    AnimatedTexture(SDL_Texture* texture, const int& w, const int& h, const int& ticks, const bool& paused);
    ~AnimatedTexture();
    /**
     * @brief Return the current animated viewport
     * @return SDL_Rect*
     */
    [[nodiscard]] SDL_Rect* getAnimatedViewport();
    /**
     * @brief Shall be called after all the viewports is added to finish the process
     */
    void addViewportDone();

    void               updateTexture();
    void               runCycles(const int& cycles);
    [[nodiscard]] bool done() const;     // Animation is last frame
    [[nodiscard]] int  getTicks() const; // Return the maximum number of ticks

  private:
  protected:
    bool      mPaused; // Texture is paused
    int       mView;
    int       mCycles;
    const int mTicks;
    int       mCurrentTicks;
    SDL_Rect  mCurrentViewport;
};
}