#pragma once
#include <SDL3/SDL.h>
#include <vector>

namespace Graphics {
class AnimatedTexture {
  public:
    AnimatedTexture();
    AnimatedTexture(SDL_Texture* texture);
    ~AnimatedTexture();

    SDL_Texture* getTexture();
    SDL_FRect* getViewport();
    void                    addViewport(const SDL_FRect& view);
    void                    nextViewport();
    [[nodiscard]] SDL_FRect getViewport() const;
    SDL_Texture*           mTexture;
  private:
  protected:
    int                    mView;

    SDL_FRect              mCurrentViewport;
    std::vector<SDL_FRect> mViewports;
};
}