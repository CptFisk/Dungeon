#pragma once
#include <SDL.h>
#include <graphics/types/textureTypes.hpp>
#include <vector>

namespace Graphics {
/**
 * @brief Base class containing standard information about images.
 */
class Texture {
  public:
    Texture(SDL_Texture* texture, const int& w, const int& h, TextureTypes type);
    virtual ~Texture();
    /**
     * @brief Get the reference to SDL_Texture*
     * @return SDL_Texture*&
     */
    [[nodiscard]] SDL_Texture*& getTexture();
    /**
     * @brief Change the value of @refitem mWidth, not that this dont change the size of SDL_Texture*
     * @param width New width
     */
    [[maybe_unused]] void setWidth(const int& width);
    /**
     * @brief Change the value of @refitem mHeight, not that this dont change the size of SDL_Texture*
     * @param width New height
     */
    [[maybe_unused]] void setHeight(const int& height);
    /**
     * @brief Get the width of the texture
     */
    [[nodiscard]] [[maybe_unused]] constexpr int getWidth() const { return mWidth; };
    /**
     * @brief Get the width of texture as float
     * @return
     */
    [[nodiscard]] [[maybe_unused]] constexpr float getWidthF() const { return static_cast<float>(mWidth); };
    /**
     * @brief Get the height of the object
     *
     */
    [[nodiscard]] [[maybe_unused]] constexpr int getHeight() const { return mHeight; };
    /**
     * @brief Get the height of the object as float
     *
     */
    [[nodiscard]] [[maybe_unused]] constexpr float getHeightF() const { return static_cast<float>(mHeight); };
    /**
     * @brief Get the type object
     */
    [[nodiscard]] constexpr TextureTypes getType() const { return mType; };
    /**
     * @brief Add a viewport to the graphic
     *
     * @param viewport Viewport to add
     */
    void addViewport(const SDL_Rect& viewport);
    /**
     * @brief Get a specific viewport from the vector
     *
     * @param n Position to fetch
     * @return SDL_Rect&
     */
    [[nodiscard]] SDL_Rect& getViewport(const size_t& n);
    /**
     * @brief Get the random viewport from the  vector
     *
     * @return SDL_Rect&
     */
    [[nodiscard]] SDL_Rect& getRandomViewport();
    /**
     * @brief Get the reference to all viewports
     * @return std::vector<SDL_Rect>&
     */
    [[nodiscard]] std::vector<SDL_Rect>& getViewports();

  protected:
    std::vector<SDL_Rect> mViewports;
    SDL_Texture*          pTexture; // SDL_Texture
    int                   mHeight;  // Texture Height
    int                   mWidth;   // Texture width
  private:
    const TextureTypes mType; // Texture type
};
}
