#pragma once
#include <SDL.h>
#include <any>
#include <common/include.hpp>
#include <graphics/structures.hpp>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/simpleTexture.hpp>
#include <graphics/types/textureTypes.hpp>
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

    /**
     * @brief Generate a text as texture
     * @param text Text to be generated
     * @param size Size of the text, default and min value is 8
     */
    typeTextTexture generateText(std::string text, const int& size = 8);

    struct typeTextureInfo {
        std::any     Texture;
        TextureTypes Type;
    };

    template<typename T>
    T* getTexture(const std::string& name) {
        auto it = mGraphics.find(name);
        if (it != mGraphics.end()) {
            try {
                return std::any_cast<T>(&it->second.Texture);
            } catch (const std::bad_any_cast& e) {
                std::cerr << name << std::endl;
                throw std::runtime_error(e.what());
            }
        } else
            std::cerr << "Cant locate " << name << std::endl;
        return nullptr;
    }

    template<typename T>
    void addTexture(const std::string& name, T texture, TextureTypes type) {
        switch (type) {
            case TextureTypes::AnimatedTexture:
                mAnimatedTextures.push_back(std::any_cast<AnimatedTexture*>(texture));
                mGraphics[name] = { texture, type };
                break;
            case TextureTypes::LightningTexture:
                mLightningTextures.push_back(std::any_cast<AnimatedTexture*>(texture));
                mGraphics[name] = { texture, type };
                break;
            case TextureTypes::BaseTexture:
            case TextureTypes::GeneratedTexture:
                mGraphics[name] = { texture, type };
            default:
                break;
        }
    }

    void                                              updateAnimatedTexture();
    void                                              updateLightningTexture();
    std::vector<std::pair<TextureTypes, std::string>> getAllTextureNames() {
        std::vector<std::pair<TextureTypes, std::string>> textures;
        for (auto& graphic : mGraphics) {
            if (graphic.second.Type == TextureTypes::BaseTexture || graphic.second.Type == TextureTypes::AnimatedTexture)
                textures.push_back({ graphic.second.Type, graphic.first });
        }
        return textures;
    }

    [[nodiscard]] TextureTypes getTextureType(const std::string& texture);

  protected:
    void loadGraphics(const std::string& folderPath);    // Start function
    void loadJSON(const std::string& fileName);          // Load the header and select sub function
    void loadBaseTexture(const std::string& jsonString); // Sub function for base-texture
    void loadAnimatedTexture(const std::string& jsonString);
    void loadLightningTexture(const std::string& jsonString); // Sub function for lightning effects
    void loadGeneratedTexture(const std::string& jsonString);
    void loadTextTexture(const std::string& jsonString); // Sub function for text textures

    // Functions to generate shapes
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

  private:
    std::unordered_map<std::string, typeTextureInfo> mGraphics; // Storage for all textures
    SDL_Renderer*                                    pRenderer;

    std::vector<AnimatedTexture*> mAnimatedTextures;  // Textures that should be updated cyclic
    std::vector<AnimatedTexture*> mLightningTextures; // Textures that should be updated cyclic
};
}