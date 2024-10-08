#include <graphics/floatingText.hpp>
#include <utility/math.hpp>
namespace Graphics {

FloatingText::FloatingText(SDL_FPoint position, const int& value, const int& visibility, SDL_Texture*& texture, const float& scale)
  : pTexture(texture) {
    // All is prepared, now starting to calculate
    auto numbers = Utility::splitNumbers(value);
    int  pos     = 0; // Current position
    for (const auto& number : numbers) {
        auto& posX = position.x;
        auto& posY = position.y;

    }
}

typeDrawData
FloatingText::getFloatingText() {
    return typeDrawData{ pTexture, nullptr, &mPosition };
}

}