#pragma once
#include <SDL.h>
#include <array>
#include <common/scale.hpp>
#include <graphics/types/drawData.hpp>
#include <graphics/types/userInterfaceTexture.hpp>
#include <string>
#include <unordered_map>

namespace Engine::UI {

enum TextboxSize {
    Small,  // Height of X
    Medium, // Height of Y,
    Large   // Height of Z
};

class Textbox {
  public:
    Textbox(SDL_Renderer*& renderer, Common::typeScale& scale);
    ~Textbox();

    /**
     * @brief Generate boxes based on screen dimensions
     */
    void generateBoxes();

    /**
     * @brief Add a new font to the list
     * @param name
     * @param texture
     */
    void addFont(const std::string& name, Graphics::UserInterfaceTexture* texture);
    /**
     * @brief Add Different sizes to the textbox
     * @param size Small, Medium or Large
     * @param start Start texture (left)
     * @param center Center texture (middle)
     * @param end End texture (right)
     */
    void addElements(const TextboxSize&              size,
                     Graphics::UserInterfaceTexture* start,
                     Graphics::UserInterfaceTexture* center,
                     Graphics::UserInterfaceTexture* end);
    /**
     * @brief Get all the draw data
     */
    Graphics::typeDrawData getTextbox(const TextboxSize& size);

  protected:
  private:
    Common::typeScale& mScale;

    struct typeElements {
        std::array<Graphics::UserInterfaceTexture*, 3> Graphics; // Contains the 3 UserInterface elements
        TextboxSize                                    Size;
    };
    std::array<typeElements, 3>           mElements;  // Hold all the textures that is used to combine and generate the box
    std::array<SDL_Texture*, 3>           mTextures;  // Pre-generated textures for each size
    std::array<SDL_FRect, 3>              mPositions; // Positions for textboxes
    std::array<Graphics::typeDrawData, 3> mTextboxes; // The final product
    SDL_Renderer*&                        pRenderer;  // Reference to the renderer, used when generating boxes
};

}