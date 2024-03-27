#pragma once
#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>

namespace Graphics {
/**
 * @brief Holds a basic texture and all the available viewports.
 */
struct typeSimpleTexture {
    SDL_Texture* Texture; // Texture
    const int  Width;   // Texture width
    const int  Height;  // Texture height

    /**
     * @brief Return the texture and a viewport.
     * @param n Element to fetch
     */
    std::pair<SDL_Texture*, SDL_FRect> operator[](size_t n) const;

    typeSimpleTexture();    //Default constructor
    explicit typeSimpleTexture(SDL_Texture* texture, const int& w, const int& h);

    typeSimpleTexture& operator=(const typeSimpleTexture& other); //Operator overload
  private:
    std::vector<SDL_FRect> Views; // Views
};


}