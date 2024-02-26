#pragma once
#include <SDL3/SDL.h>
#include <any>
#include <common/include.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/structures.hpp>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace Graphics {
class Graphics {
  public:
    Graphics(SDL_Renderer* renderer, Common::typeScale& scale);
    ~Graphics();
    void init();
    void generateSquare(const std::string& name,
                        const int&         width,
                        const int&         height,
                        const Uint8&       r,
                        const Uint8&       g,
                        const Uint8&       b,
                        const Uint8&       a);
    void generateCircle(const std::string& name,   // Name of texture
                        const float&       radius, // Radius
                        const Uint8&       r1,     // Start red color
                        const Uint8&       r2,     // End red color
                        const Uint8&       g1,     // Start green color
                        const Uint8&       g2,     // End green color
                        const Uint8&       b1,     // Start blue color
                        const Uint8&       b2,     // End blue color
                        const Uint8&       a);           // Alpha channel

    struct typeTextureInfo {
        std::any     Texture;
        TextureTypes Type;
    };

    template<typename T>
    T getTexture(const std::string& name) {
        auto it = mGraphics.find(name);
        if (it != mGraphics.end()) {
            try {
                return std::any_cast<T>(it->first);
            } catch (const std::bad_any_cast& e) {
                throw std::runtime_error(e.what());
            }
        } else
            throw std::out_of_range(name);
    }

    void updateAnimatedTexture();

  protected:
    SDL_Texture* loadImage(const std::string& filename);
    void         loadGraphics(const std::string& folderPath);
    void         loadBaseTiles(const Common::typeHeaderJSON& header, const std::string& jsonString);
    void         loadObjectAnimation(const Common::typeHeaderJSON& header, const std::string& jsonString);
    void         loadObjectGeneration(const Common::typeHeaderJSON& header, const std::string& jsonString);

  private:
    Common::typeScale&                               mScale;
    std::unordered_map<std::string, typeTextureInfo> mGraphics; // Storage for all textures
    SDL_Renderer*                                    pRenderer;
    std::vector<AnimatedTexture*>            mAnimatedTextures;
    template<typename T>
    void addTexture(const std::string& name, T texture, TextureTypes type) {
        auto it = mGraphics.find(name);
        if (it == mGraphics.end()) {
            // mGraphics[name] = typeTextureInfo(texture, type);
            mGraphics[name] = { texture, type };
        }
        if (type == ANIMATED_TEXTURE)
            mAnimatedTextures.push_back(std::any_cast<AnimatedTexture*>(&texture));
    }
};
}