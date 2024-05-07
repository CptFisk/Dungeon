#pragma once
#include <SDL3/SDL.h>
#include <any>
#include <common/include.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/structures.hpp>
#include <graphics/types/simpleTexture.hpp>
#include <iostream>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#define GET_ANIMATED(VAR) mGraphics->getTexture<Graphics::AnimatedTexture*>(VAR)
#define GET_SIMPLE(VAR)   mGraphics->getTexture<Graphics::typeSimpleTexture>(VAR)
#define GET_SDL(VAR)      mGraphics->getTexture<SDL_Texture*>(VAR)

namespace Graphics {
class Graphics {
  public:
    explicit Graphics(SDL_Renderer* renderer);
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

    /**
     * @brief Generate a text as texture
     * @param text Text to be generated
     * @param width Width of each letter
     * @param height Height of each letter
     * @return
     */
    typeTextTexture generateText(std::string text, const int& size = 8);

    struct typeTextureInfo {
        std::any     Texture;
        TextureTypes Type;
    };

    template<typename T>
    T& getTexture(const std::string& name) {
        auto it = mGraphics.find(name);
        if (it != mGraphics.end()) {
            try {
                return std::any_cast<T&>(it->second.Texture);
            } catch (const std::bad_any_cast& e) {
                std::cerr << name << std::endl;
                throw std::runtime_error(e.what());
            }
        } else
            throw std::out_of_range(name);
    }

    template<typename T>
    void addTexture(const std::string& name, T texture, TextureTypes type) {
        auto it = mGraphics.find(name);
        if (it == mGraphics.end()) {
            mGraphics[name] = { texture, type };
        }
        if (type == ANIMATED_TEXTURE)
            mAnimatedTextures.push_back(std::any_cast<AnimatedTexture*>(texture));
    }

    void updateAnimatedTexture();

    std::vector<std::string> getAllTextureNames() {
        std::vector<std::string> names;
        for (auto& graphic : mGraphics) {
            if (graphic.second.Type == SIMPLE_TEXTURE)
                names.push_back(graphic.first);
        }
        return names;
    }

  protected:
    SDL_Texture* loadImage(const std::string& filename);
    void         loadGraphics(const std::string& folderPath);
    void         loadJSON(const std::string& fileName); // Load a graphical JSON
    void         loadSimpleTexture(const std::string& jsonString);
    void         loadAnimatedTexture(const std::string& jsonString);
    void         loadGeneratedTexture(const std::string& jsonString);

  private:
    std::unordered_map<std::string, typeTextureInfo> mGraphics; // Storage for all textures
    SDL_Renderer*                                    pRenderer;

    std::vector<AnimatedTexture*> mAnimatedTextures; // Textures that should be updated cyclic
};
}