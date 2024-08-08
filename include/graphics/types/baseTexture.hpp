#pragma once
#include <SDL.h>
#include <graphics/types/texture.hpp>

namespace Graphics {
/**
 * @brief Holds a basic texture and all the available viewports.
 */
class BaseTexture : public Texture {
    using Texture::Texture;

  public:
    BaseTexture(SDL_Texture* texture, const int& w, const int& h);
    ~BaseTexture();
};

}