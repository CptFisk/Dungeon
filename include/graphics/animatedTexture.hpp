#pragma once
#include <SDL.h>
#include <vector>

namespace Graphics {
class AnimatedTexture {
  public:
    AnimatedTexture();
    AnimatedTexture(SDL_Texture* texture, const int& ticks);
    ~AnimatedTexture();

    [[nodiscard]] SDL_Texture* getTexture() const;
    SDL_Rect*                  getViewport();
    void                       addViewport(const SDL_Rect& view);
    void                       updateTexture();
    [[nodiscard]] SDL_Rect     getViewport() const;

    bool done() const;  //Animation is last frame

  private:
  protected:
    int                   mView;
    const int             mTicks;
    int                   mCurrentTicks;
    SDL_Rect              mCurrentViewport;
    SDL_Texture*          mTexture;
    std::vector<SDL_Rect> mViewports;
};
}