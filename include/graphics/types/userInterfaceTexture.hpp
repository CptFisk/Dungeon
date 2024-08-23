#pragma once
#include <SDL.h>
#include <graphics/types/texture.hpp>

namespace Graphics {
/**
 * @brief Texture class for UI objects
 */
class UserInterfaceTexture : public Texture {
    using Texture::Texture;

  public:
    /**
     * @brief Constructor for userinterface objects, derived from Texture
     * @param texture Texture
     * @param w Width of texture
     * @param h Height of texture
     * @param top Margin top
     * @param bottom Margin bottom
     * @param left Margin left
     * @param right Margin right
     */
    UserInterfaceTexture(SDL_Texture* texture,
                         const int&   w,
                         const int&   h,
                         const int&   top,
                         const int&   bottom,
                         const int&   left,
                         const int&   right);
    ~UserInterfaceTexture() override = default;

    /**
     * @brief Return the margin (spacing) to a element from that side of the screen.
     * @brief When requesting margin for right and bottom, compensation for the texture size have been made
     * @return value as the specific type
     */
    [[nodiscard]] [[maybe_unused]] constexpr int   getMarginTop() const { return mMarginTop; };
    [[nodiscard]] [[maybe_unused]] constexpr float getMarginTopF() const { return static_cast<float>(mMarginTop); };
    [[nodiscard]] [[maybe_unused]] constexpr int   getMarginBottom() const { return mMarginBottom + mHeight; };
    [[nodiscard]] [[maybe_unused]] constexpr float getMarginBottomF() const { return static_cast<float>(mMarginBottom + mHeight); };
    [[nodiscard]] [[maybe_unused]] constexpr int   getMarginLeft() const { return mMarginLeft; };
    [[nodiscard]] [[maybe_unused]] constexpr float getMarginLeftF() const { return static_cast<float>(mMarginLeft); };
    [[nodiscard]] [[maybe_unused]] constexpr int   getMarginRight() const { return mMarginRight + mWidth; };
    [[nodiscard]] [[maybe_unused]] constexpr float getMarginRightF() const { return static_cast<float>(mMarginRight + mWidth); };
    /**
     * @brief Return the total width + margin for a element, only usable on top and left
     * @example getTotalTop will return margin to top + graphic height
     * @return value as specific type
     */
    [[nodiscard]] [[maybe_unused]] constexpr int   getTotalTop() const { return mMarginTop + mHeight; };
    [[nodiscard]] [[maybe_unused]] constexpr float getTotalTopF() const { return static_cast<float>(mMarginTop + mHeight); };
    [[nodiscard]] [[maybe_unused]] constexpr int   getTotalLeft() const { return mMarginLeft + mWidth; };
    [[nodiscard]] [[maybe_unused]] constexpr float getTotalLeftF() const { return static_cast<float>(mMarginLeft + mWidth); };

  protected:
  private:
    const int mMarginTop;    // Margin to top of screen
    const int mMarginBottom; // Margin to bottom of screen
    const int mMarginLeft;   // Margin to left side of screen
    const int mMarginRight;  // Margin to right side of screen
};

}