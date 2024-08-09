#pragma once
#include <SDL.h>
#include <graphics/types/texture.hpp>

namespace Graphics {
/**
 * @brief Holds a basic texture and all the available viewports.
 */
class NumberTexture : public Texture {
    using Texture::Texture;

  public:
    NumberTexture(SDL_Texture* texture, const int& w, const int& h);
    ~NumberTexture();
};

}