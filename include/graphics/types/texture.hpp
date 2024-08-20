#pragma once
#include <SDL.h>
#include <graphics/types/textureTypes.hpp>
#include <vector>

namespace Graphics {
/**
 * @brief Base class containting standard information about images.
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
     * @brief Get the width of the texture
     */
    [[nodiscard]] int getWidth() const;
    /**
     * @brief Get the width of texture as float
     * @return
     */
    [[nodiscard]] float getWidthF() const;
    /**
     * @brief Get the height of the object
     *
     */
    [[nodiscard]] int getHeight() const;
    /**
     * @brief Get the height of the object as float
     *
     */
    [[nodiscard]] float getHeightF() const;
    /**
     * @brief Get the type object
     */
    [[nodiscard]] TextureTypes getType() const;
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
  private:
    const int          mHeight; // Texture Height
    const int          mWidth;  // Texture width
    const TextureTypes mType;   // Texture type
};
}
