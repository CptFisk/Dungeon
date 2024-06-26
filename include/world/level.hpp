#pragma once
#include <SDL3/SDL.h>
#include <graphics/structures.hpp>
#include <string>
#include <unordered_map>
#include <common/structures.hpp>

namespace Engine {
class Level {
    struct Base {
        SDL_Texture* Texture;
        SDL_FRect    View;
        SDL_FRect    Position;
    };

  public:
    Level(SDL_Renderer* renderer, const Common::typeScale& scale);
    ~Level();
    void generateLevel(const Graphics::typeSimpleTexture& base);
    void drawLevel();

  protected:
  private:
    Base mMap[192];
    Common::typeScale mScale;
    SDL_Renderer* pRenderer;
};
}