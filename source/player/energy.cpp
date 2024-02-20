#include <player/energy.hpp>
#include <iostream>

namespace Player {
Energy::Energy(const Common::typeScale& scale, const Graphics::BaseTexture& baseTexture, SDL_Renderer* renderer)
  : mEnergy(100.0)
  , mBaseTexture(baseTexture)
  , pRenderer(renderer) {}

Energy::~Energy() {}

void
Energy::draw() {
    SDL_FRect edgeLeft = {50.0,100.0,60,60};
    if(SDL_RenderTexture(pRenderer, mBaseTexture.Texture, &mBaseTexture.Views[0], &edgeLeft) != 0){
        std::cout << SDL_GetError() << std::endl;
    }
}
}