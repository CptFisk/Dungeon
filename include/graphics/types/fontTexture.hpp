#pragma once
#include <SDL.h>
#include <graphics/types/texture.hpp>
#include <string>
#include <unordered_map>

namespace Graphics {
/**
 * @brief Holds a basic texture and all the available viewports.
 */
class FontTexture : public Texture {
    using Texture::Texture;

  public:
    FontTexture(SDL_Texture* texture, SDL_Renderer*& renderer);
    ~FontTexture() override;

    SDL_Texture*& generateSentence(const std::string& sentence);

  protected:
    SDL_Renderer*&                                pRenderer; // Reference to the renderer
    std::unordered_map<std::string, SDL_Texture*> mTexts;
};

}