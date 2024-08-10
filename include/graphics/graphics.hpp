#pragma once
#include <SDL.h>
#include <any>
#include <common/include.hpp>
#include <error.hpp>
#include <graphics/structures.hpp>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/baseTexture.hpp>
#include <graphics/types/generatedTexture.hpp>
#include <graphics/types/textTexture.hpp>
#include <graphics/types/textureTypes.hpp>
#include <iostream>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#define GET_ANIMATED(VAR)  static_cast<Graphics::AnimatedTexture*>(mGraphics->getTexture(VAR))
#define GET_BASE(VAR)      static_cast<Graphics::BaseTexture*>(mGraphics->getTexture(VAR))
#define GET_GENERATED(VAR) static_cast<Graphics::GeneratedTexture*>(mGraphics->getTexture(VAR))
// #define GET_SIMPLE(VAR)   mGraphics->getTexture<Graphics::BaseTexture>(VAR)
// #define GET_SDL(VAR)      mGraphics->getTexture<SDL_Texture*>(VAR)

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

    Texture* getTexture(const std::string& name) {
        ASSERT_WITH_MESSAGE(mGraphics.find(name) == mGraphics.end(), name << " dont exist");
        return mGraphics[name];
    }

    void addTexture(const std::string& name, Texture* texture) {
        ASSERT_WITH_MESSAGE(mGraphics.find(name) != mGraphics.end(), name << " already exists")

        switch (texture->getType()) {
            case TextureTypes::GeneratedTexture:
            case TextureTypes::BaseTexture:
                mGraphics[name] = texture;
                break;
            case TextureTypes::AnimatedTexture:
            case TextureTypes::LightningTexture:
            case TextureTypes::Text:
            case TextureTypes::Number:
                mGraphics[name] = texture;
                mAnimatedTextures.push_back(&mGraphics[name]);
                break;
        }
    }

    void                                              updateAnimatedTexture();
    std::vector<std::pair<TextureTypes, std::string>> getAllTextureNames() {
        std::vector<std::pair<TextureTypes, std::string>> textures;
        for (auto& [name, graphic] : mGraphics) {
            if (graphic->getType() == TextureTypes::BaseTexture || graphic->getType() == TextureTypes::AnimatedTexture)
                textures.push_back({ graphic->getType(), name });
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
    std::unordered_map<std::string, Texture*> mGraphics; // Storage for all textures
    SDL_Renderer*                             pRenderer;

    std::vector<Texture**>         mAnimatedTextures;  // Textures that should be updated cyclic
    std::vector<AnimatedTexture**> mLightningTextures; // Textures that should be updated cyclic
};
}