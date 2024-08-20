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
    UserInterfaceTexture(SDL_Texture* texture, const int& w, const int& h, const int& top, const int& bottom, const int& left, const int& right);
    ~UserInterfaceTexture() = default;

    /**
     * brief Return the margin for element to top of screen
     * @return Margin top
     */
    [[nodiscard]] [[maybe_unused]] int getMarginTop() const;
    /**
     * brief Return the margin for element to bottom of screen
     * @return Margin bottom
     */
    [[nodiscard]] [[maybe_unused]]int getMarginBottom() const;
    /**
     * brief Return the margin for element to the left side of screen
     * @return Margin left
     */
    [[nodiscard]] [[maybe_unused]]int getMarginLeft() const;
    /**
     * brief Return the margin for element to the right side of screen
     * @return Margin right
     */
    [[nodiscard]] [[maybe_unused]]int getMarginRight() const;

  protected:
  private:
    const int mMarginTop;    // Margin to top of screen
    const int mMarginBottom; // Margin to bottom of screen
    const int mMarginLeft;   // Margin to left side of screen
    const int mMarginRight;  // Margin to right side of screen
};

}