#pragma once
#include <SDL3/SDL.h>
#include <common/include.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/structures.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace Graphics {
class Graphics {
  public:
    Graphics(SDL_Renderer* renderer, Common::Scale& scale);
    ~Graphics();
    void             init();
    void             generateSquare(const std::string& name,
                                    const int&         width,
                                    const int&         height,
                                    const Uint8&       r,
                                    const Uint8&       g,
                                    const Uint8&       b,
                                    const Uint8&       a);
    void             generateCircle(const std::string& name,   // Name of texture
                                    const float&       radius, // Radius
                                    const Uint8&       r1,     // Start red color
                                    const Uint8&       r2,     // End red color
                                    const Uint8&       g1,     // Start green color
                                    const Uint8&       g2,     // End green color
                                    const Uint8&       b1,     // Start blue color
                                    const Uint8&       b2,     // End blue color
                                    const Uint8&       a);           // Alpha channel
    SDL_Texture*     getTexture(const std::string& name);
    BaseTexture      getBaseTexture(const std::string& name);
    AnimatedTexture* getAnimatedTexture(const std::string& name);
    
    void addTexture(const std::string& name, SDL_Texture* texture);

    void updateAnimatedTexture();

  protected:
    SDL_Texture* loadImage(const std::string& filename);
    void         loadGraphics(const std::string& folderPath);
    void         loadBaseTiles(const Common::HeaderJSON& header, const std::string& jsonString);
    void         loadObjectAnimation(const Common::HeaderJSON& header, const std::string& jsonString);
    void         loadObjectGeneration(const Common::HeaderJSON& header, const std::string& jsonString);

  private:
    Common::Scale& mScale;

    std::unordered_map<std::string, AnimatedTexture*> mAnimatedTextures;
    std::unordered_map<std::string, BaseTexture>      mBaseTextures;
    std::unordered_map<std::string, SDL_Texture*>     mTextures;
    SDL_Renderer*                                     pRenderer;
};
}