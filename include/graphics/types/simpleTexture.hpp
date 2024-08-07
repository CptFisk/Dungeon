#pragma once
#include <SDL.h>
#include <nlohmann/json.hpp>

namespace Graphics {
/**
 * @brief Holds a basic texture and all the available viewports.
 */
class typeSimpleTexture {
  public:
    typeSimpleTexture(); // Default constructor
    explicit typeSimpleTexture(SDL_Texture* texture, const int& w, const int& h);

    const int Width;  // Texture width
    const int Height; // Texture height

    /**
     * @brief Return the texture and a viewport.
     * @param n Element to fetch
     */
    [[nodiscard]] std::pair<SDL_Texture*, SDL_Rect> operator[](size_t n) const;
    /**
     * @brief Returns the texture
     * @return Pointer to the texture
     */
    [[nodiscard]] SDL_Texture*& getTexture();
    /**
     * @brief Add a new viewport
     * @param view Viewport to add
     */
    void addView(const SDL_Rect& view);
    /**
     * @brief Return a specific viewport
     * @param n Element to fetch
     * @return Reference to viewport
     */
    [[nodiscard]] SDL_Rect& getView(size_t n);
    /**
     * @brief Returns a random viewport
     * @return Reference to viewport
     */
    [[nodiscard]] SDL_Rect& getRandomView();

    typeSimpleTexture& operator=(const typeSimpleTexture& other); // Operator overload
  private:
    std::vector<SDL_Rect> Views;   // Views
    SDL_Texture*          Texture; // Texture
};

}