#include <global.hpp>
#include <graphics/graphics.hpp>
#include <ui/userInterface.hpp>
namespace Engine::UI {

void
UserInterface::calculateSoul() {
    auto& icon = mSoulDrawData.front();
    int   w, h;
    SDL_QueryTexture(icon.Texture, nullptr, nullptr, &w, &h);
    icon.Position->x = mScale.scaledWindowWidthF - 32.0f;
    icon.Position->y = 16.0f;
    icon.Position->w = 16.0f;
    icon.Position->h = 16.0f;
}

void
UserInterface::updateSoul() {
    auto& number   = mSoulDrawData.back();
    auto  font     = GET_TTF(DEFAULT_FONT);
    number.Texture = font->generateSentence(std::to_string(mSoulCount), { 0x33, 0x33, 0x33, 255 });
    // Get dimension
    int w, h;

    SDL_QueryTexture(number.Texture, nullptr, nullptr, &w, &h);
    // Calculate x position
    const auto x       = mScale.scaledWindowWidthF - 38.0f - static_cast<float>(w);
    const auto offset  = (16 - h) / 2;
    number.Position->x = x;
    number.Position->y = 16.0f + static_cast<float>(offset);
    number.Position->w = static_cast<float>(w);
    number.Position->h = static_cast<float>(h);
    number.Viewport    = nullptr;
}

std::vector<Graphics::typeDrawData>
UserInterface::getSoul() const {
    return mSoulDrawData;
}

}