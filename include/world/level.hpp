#pragma once
#include <string>
#include <unordered_map>

#include <SDL3/SDL.h>

#include <graphics/structures.hpp>

namespace Engine{
class Level{
    struct Base{
        SDL_Texture* Texture;
        SDL_FRect View;
        SDL_FRect Position;
    };
  public:
    Level(SDL_Renderer* renderer);
    ~Level();
    void generateLevel(const Graphics::BaseTexture& base);
    void drawLevel();
  protected:
  private:
    Base mMap[192];
    SDL_Renderer* pRenderer;
    };
}