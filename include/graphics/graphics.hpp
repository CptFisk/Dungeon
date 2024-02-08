#pragma once
#include <SDL3/SDL.h>
#include <engine/structures.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/structures.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace Graphics {
class Graphics {
  public:
    Graphics(SDL_Renderer* renderer, float& scaleX, float& scaleY);
    ~Graphics();
    void             generateSquare(const std::string& name,
                                    const int&         width,
                                    const int&         height,
                                    const Uint8&       r,
                                    const Uint8&       g,
                                    const Uint8&       b,
                                    const Uint8&       a);
    void             generateCircle(const std::string& name,
                                    const float&       radius,
                                    const Uint8&       r,
                                    const Uint8&       g,
                                    const Uint8&       b,
                                    const Uint8&       a);
    SDL_Texture*     getTexture(const std::string& name);
    BaseTexture      getBaseTexture(const std::string& name);
    AnimatedTexture* getAnimatedTexture(const std::string& name);

    void updateAnimatedTexture();
  protected:
    SDL_Texture* loadImage(const std::string& filename);
    void         loadGraphics(const std::string& folderPath);
    void         loadBaseTiles(const Engine::HeaderJSON& header, const std::string& jsonString);
    void         loadObjectAnimation(const Engine::HeaderJSON& header, const std::string& jsonString);

  private:
    float& mScaleX;
    float& mScaleY;

    std::unordered_map<std::string, AnimatedTexture*> mAnimatedTextures;
    std::unordered_map<std::string, BaseTexture>      mBaseTextures;
    std::unordered_map<std::string, SDL_Texture*>     mTextures;
    SDL_Renderer*                                     pRenderer;
};
}