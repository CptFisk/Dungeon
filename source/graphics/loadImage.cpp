#include <stdexcept>
#include <iostream>
#include <SDL_image.h>

#include <graphics/graphics.hpp>

namespace Graphics{

SDL_Texture*
Graphics::loadImage(const std::string& filename) {
    SDL_Texture* texture = IMG_LoadTexture(pRenderer, filename.c_str());
    if(texture == nullptr){
        std::cerr << "Can load " << filename;
        throw std::runtime_error("Cant load texture");
    }
    return texture;
}


}