#pragma once
#include <SDL.h>
#include <graphics/types/baseTexture.hpp>
#include <graphics/types/drawData.hpp>
#include <graphics/types/font.hpp>
#include <string>

namespace Graphics {
/**
 * @brief Create a text that disappear after a time
 */

class DisappearingText {
  public:
    DisappearingText(const int ticks, const SDL_FPoint& position, Font* font, const std::string& text);
    ~DisappearingText() = default;
    typeDrawData getDisappearingText();

    constexpr bool expired() { return (mCurrentTicks++ > mTicks) ? true : false; };

  private:
  protected:
    const int    mTicks;        // Maximum number of ticks
    int          mCurrentTicks; // Current ticks
    SDL_FRect    mPosition;
    typeDrawData mDrawData;
};

}