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
    void                        addViewport(const SDL_Rect& view);
    void                        updateTexture();
    void                        runCycles(const int& cycles);
    [[nodiscard]] SDL_Rect      getViewport() const;

    [[nodiscard]] bool done() const;     // Animation is last frame
    [[nodiscard]] int  getTicks() const; // Return the maximum number of ticks
  private:
  protected:
    bool                  mPaused;
    int                   mView;
    int                   mCycles;
    const int             mTicks;
    int                   mCurrentTicks;
    SDL_Rect              mCurrentViewport;
    SDL_Texture*          mTexture;
    std::vector<SDL_Rect> mViewports;
};
}