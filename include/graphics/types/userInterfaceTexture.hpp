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
    ~UserInterfaceTexture() = default;

    /**
     * @brief Return the margin (spacing) to a element from that side of the screen.
     * @brief When requesting margin for right and bottom, compensation for the texture size have been made
     * @return value as the specific type
     */
    [[nodiscard]] [[maybe_unused]] int   getMarginTop() const;
    [[nodiscard]] [[maybe_unused]] float getMarginTopF() const;
    [[nodiscard]] [[maybe_unused]] int   getMarginBottom() const;
    [[nodiscard]] [[maybe_unused]] float getMarginBottomF() const;
    [[nodiscard]] [[maybe_unused]] int   getMarginLeft() const;
    [[nodiscard]] [[maybe_unused]] float getMarginLeftF() const;
    [[nodiscard]] [[maybe_unused]] int   getMarginRight() const;
    [[nodiscard]] [[maybe_unused]] float getMarginRightF() const;

  protected:
  private:
    const int mMarginTop;    // Margin to top of screen
    const int mMarginBottom; // Margin to bottom of screen
    const int mMarginLeft;   // Margin to left side of screen
    const int mMarginRight;  // Margin to right side of screen
};

}