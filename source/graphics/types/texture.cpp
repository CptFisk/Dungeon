#include <error.hpp>
#include <graphics/types/texture.hpp>
#include <random>

namespace Graphics {
Texture::Texture(SDL_Texture* texture, const int& w, const int& h, TextureTypes type)
  : pTexture(texture)
  , mWidth(w)
  , mHeight(h)
  , mType(type) {}

Texture::~Texture() {
    SDL_DestroyTexture(pTexture);
}

SDL_Texture*&
Texture::getTexture() {
    return pTexture;
}

void
Texture::setHeight(const int& height) {
    mHeight = height;
}

void
Texture::setWidth(const int& width) {
    mWidth = width;
}

void
Texture::addViewport(const SDL_Rect& viewport) {
    mViewports.push_back(viewport);
}

SDL_Rect&
Texture::getViewport(const size_t& n) {
    ASSERT_WITH_MESSAGE(n > mViewports.size(), "Viewport dont exist")
    return mViewports[n];
}

SDL_Rect&
Texture::getRandomViewport() {
    return mViewports[rand() % mViewports.size()];
}

std::vector<SDL_Rect>&
Texture::getViewports() {
    return mViewports;
}

}