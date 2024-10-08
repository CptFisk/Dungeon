#pragma once
#include <SDL.h>
#include <graphics/types/texture.hpp>

namespace Graphics {
/**
 * @brief Holds a basic texture and all the available viewports.
 */
class FontTexture : public Texture {
    using Texture::Texture;

  public:
    FontTexture(SDL_Texture* texture, SDL_Renderer*& renderer, const int& w, const int& h);
    ~FontTexture();
  protected:
    SDL_Renderer*& pRenderer;   //Reference to the renderer
};

}