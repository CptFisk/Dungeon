#pragma once
#include <SDL.h>
#include <vector>

namespace Graphics {
class AnimatedTexture {
  public:
    AnimatedTexture();
    AnimatedTexture(SDL_Texture* texture, const int& ticks, const bool& paused);
    ~AnimatedTexture();

    [[nodiscard]] SDL_Texture*& getTexture();
    SDL_Rect*                   getViewport();
    SDL_Rect*                   getViewport(const int& pos);
    void                        addViewport(const SDL_Rect& view);
    void                        updateTexture();
    void                        runCycles(const int& cycles);
    std::vector<SDL_Rect>       getViewports();    // Get all the viewports for the animations
    [[nodiscard]] bool          done() const;      // Animation is last frame
    [[nodiscard]] int           getTicks() const;  // Return the maximum number of ticks

  private:
  protected:
    bool                  mPaused;
    int                   mView;
    int                   mCycles;
    const int             mTicks;
    int                   mCurrentTicks;
    SDL_Rect              mCurrentViewport;
    std::vector<SDL_Rect> mViewports;
    SDL_Texture*          mTexture;
};
}