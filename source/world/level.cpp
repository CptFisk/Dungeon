#include <random>
#include <world/level.hpp>

namespace Engine {
Level::Level(SDL_Renderer* renderer, const Engine::Scale& scale) : pRenderer(renderer), mScale(scale){}
Level::~Level() {}

void
Level::generateLevel(const Graphics::BaseTexture& base) {
    std::random_device rd;
    std::mt19937       gen(rd());

    int pos = 0;
    for (int y = 1; y < 11; y++) {
        for (int x = 1; x < 15; x++) {
            // Selecting random time
            std::uniform_int_distribution<int> distribution(
              0, base.Views.size() - 1);
            int variation        = distribution(gen);
            mMap[pos].Texture    = base.Texture;
            mMap[pos].View       = base.Views[variation];
            mMap[pos++].Position = SDL_FRect{
                static_cast<float>(x) * 50, static_cast<float>(y) * 50, 50, 50
            };
        }
    }
    printf("%i\n", pos);
}

void
Level::drawLevel() {
    for(int i = 0; i < 140; i++){
        SDL_RenderTexture(pRenderer, mMap[i].Texture, &mMap[i].View, &mMap[i].Position);
    }
}
}