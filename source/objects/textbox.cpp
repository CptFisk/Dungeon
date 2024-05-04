#include <objects/textbox.hpp>

namespace Objects {
TextBox::TextBox(const Graphics::typeTextTexture& text, const int& x, const int& y)
  : mText(std::vector<Graphics::typeTextTexture>{text})
  , mBackground{ static_cast<float>(x, static_cast<float>(y), 50, 50) } {}

TextBox::TextBox(const std::vector<Graphics::typeTextTexture>& text, const int& x, const int& y)
  : mText(std::move(text))
  , mBackground{ static_cast<float>(x, static_cast<float>(y), 50, 50) } {}
}