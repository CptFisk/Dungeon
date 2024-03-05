#include <graphics/numbers.hpp>
#include <utility/math.hpp>
namespace Graphics {
Number::Number(std::pair<float, float>      position,
               const int&                   value,
               const int&                   visibility,
               Graphics::typeSimpleTexture& texture,
               const float&                 scale)
  : mTicks(0)
  , MAX_TICKS(visibility)
  , pTexture(texture.Texture) {
    // All is prepared, now starting to calculate
    auto numbers = Utility::splitNumbers(value);
    int  pos     = 0; // Current position
    for (const auto& number : numbers) {
        auto& posX = position.first;
        auto& posY = position.second;
        mPositions.emplace_back(SDL_FRect{ posX + (static_cast<float>(pos++) * 8.0f * scale),
                                           posY,
                                           8.0f * scale,
                                           8.0f * scale},
                                &texture.Views[number]);
    }
}

Number&
Number::operator=(const Graphics::Number& other) {
    return *this;
}

bool
Number::expired() {
    if (mTicks++ > MAX_TICKS)
        return true;
    return false;
}

typeNumbersData
Number::getNumber() const {
    return { pTexture, mPositions };
}

}