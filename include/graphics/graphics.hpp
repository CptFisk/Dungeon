#pragma once
#include <SDL.h>
#include <any>
#include <common/include.hpp>
#include <error.hpp>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/baseTexture.hpp>
#include <graphics/types/font.hpp>
#include <graphics/types/generatedTexture.hpp>
#include <graphics/types/lightningTexture.hpp>
#include <graphics/types/textureTypes.hpp>
#include <graphics/types/userInterfaceTexture.hpp>
#include <iostream>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#define GET_ANIMATED(VAR)      (dynamic_cast<Graphics::AnimatedTexture*>(mGraphics->getTexture(VAR)))
#define GET_BASE(VAR)          (dynamic_cast<Graphics::BaseTexture*>(mGraphics->getTexture(VAR)))
#define GET_GENERATED(VAR)     (dynamic_cast<Graphics::GeneratedTexture*>(mGraphics->getTexture(VAR)))
#define GET_LIGHTNING(VAR)     (dynamic_cast<Graphics::LightningTexture*>(mGraphics->getTexture(VAR)))
#define GET_USERINTERFACE(VAR) (dynamic_cast<Graphics::UserInterfaceTexture*>(mGraphics->getTexture(VAR)))
#define GET_FONT(VAR)          (mGraphics->getFont(VAR))

namespace Graphics {

class Graphics {
  public:
    explicit Graphics(SDL_Renderer* renderer);
    ~Graphics();
    void init();

    Texture*     getTexture(const std::string& name);
    SDL_Texture* getSentence(const std::string& font, const std::string& sentence);
    /**
     * @brief Add a new texture to the list, the functions handles different types and bind them with corresponding functions
     * @param name Name of texture
     * @param texture Texture* class (or child=
     */
    void  addTexture(const std::string& name, Texture* texture);
    void  addFont(const std::string& name, Font* font);
    Font* getFont(const std::string& name);
    /**
     * @brief Update all animated textures
     *
     */
    void updateAnimatedTexture();
    /**
     * @brief Fetch all textures that can be used on maps
     *
     * @return std::vector<std::pair<TextureTypes, std::string>>
     */
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
    void loadFontTexture(const std::string& jsonString);          // Load a font
    void loadUserInterfaceTexture(const std::string& jsonString); // Sub function for loading UI elements
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
    std::unordered_map<std::string, Font*>    mFonts;    // Storage for all fonts
    SDL_Renderer*                             pRenderer;

    std::vector<Texture**>         mAnimatedTextures;  // Textures that should be updated cyclic
    std::vector<AnimatedTexture**> mLightningTextures; // Textures that should be updated cyclic
};
}