#pragma once
#include <SDL.h>
#include <graphics/types/texture.hpp>

namespace Graphics {
/**
 * @brief Holds a basic texture and all the available viewports.
 */
class SimpleTexture : public Texture {
    using Texture::Texture;

  public:
    SimpleTexture(SDL_Texture* texture, const int& w, const int& h);
    ~SimpleTexture();
};

}