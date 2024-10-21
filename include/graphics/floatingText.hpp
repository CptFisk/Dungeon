#pragma once
#include <SDL.h>
#include <common/scale.hpp>
#include <graphics/types/drawData.hpp>
#include <memory>
#include <utility>
#include <vector>

namespace Graphics {
/**

 */
class FloatingText {
  public:
    FloatingText(SDL_FPoint position, SDL_Texture*& texture, const int& w, const int& h, const double long& duration);
    ~FloatingText() = default;

    bool expired();

    typeDrawData getFloatingText();

  private:
  protected:
    const double long mDuration;
    double long       mTicks;
    SDL_Texture*      pTexture; // Reference to "font"
    SDL_FRect         mPosition;
};
}