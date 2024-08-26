#include <error.hpp>
#include <graphics/types/disappearingText.hpp>

namespace Graphics {

DisappearingText::DisappearingText(const int ticks, const SDL_FPoint& position, Graphics::Font* font, const std::string& text)
  : mTicks(ticks)
  , mCurrentTicks(0) {
    int  w, h; // Dimensions
    auto texture = font->generateSentence(text);
    ASSERT_WITH_MESSAGE(texture == nullptr, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_QueryTexture(texture, nullptr, nullptr, &w, &h) != 0, SDL_GetError())
    // Create position
    mPosition = { position.x, position.y, static_cast<float>(w), static_cast<float>(h) };

    mDrawData.Texture = texture;
    mDrawData.Viewport = nullptr;
    mDrawData.Position = &mPosition;
}

typeDrawData
DisappearingText::getDisappearingText() {
    return mDrawData;
}

}