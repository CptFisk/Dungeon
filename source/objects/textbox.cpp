#include <objects/textbox.hpp>

namespace Objects {
TextBox::TextBox(const Graphics::typeTextTexture& text, const int& x, const int& y)
  : mTexture(nullptr)
  , mBackground{ static_cast<float>((x, static_cast<float>(y)), 50, 50) } {
    combineTextures(std::vector<Graphics::typeTextTexture>{ text });
}

TextBox::TextBox(const std::vector<Graphics::typeTextTexture>& text, const int& x, const int& y)
  : mTexture(nullptr)
  , mBackground{ static_cast<float>(x, static_cast<float>(y), 50, 50) } {
    combineTextures(std::move(text));
}

TextBox::~TextBox() {
    //delete mTexture; // Cleaning
}

void
TextBox::combineTextures(const std::vector<Graphics::typeTextTexture>& texts) {
    float length = 0.0f;
    float height = 0.0f;
    for (auto text : texts) {
        length = std::max(text.Dimensions.w, length);
        height += text.Dimensions.h;
    }

    // auto texture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, length, height);
}
}