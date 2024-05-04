#pragma once
#include <vector>
#include <graphics/structures.hpp>  //Used to get typeTextTexture

namespace Objects{

class TextBox{
  public:
    TextBox(const Graphics::typeTextTexture& text, const int& x, const int& y);
    TextBox(const std::vector<Graphics::typeTextTexture>& text, const int& x, const int& y);

    const std::vector<Graphics::typeTextTexture> mText;
  private:
  protected:
    SDL_FRect mBackground;

};
}