#include <error.hpp>
#include <graphics/graphics.hpp>
#include <ui/userInterface.hpp>

namespace Engine::UI {

void
UserInterface::calculateAttributes() {
    // First we clear the current UI if its already created
    if (pAttributesBackground)
        SDL_DestroyTexture(pAttributesBackground);
    auto background = GET_USERINTERFACE("Stats");
    auto font       = GET_TTF(DEFAULT_FONT);
    pAttributesBackground =
      SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, background->getWidth(), background->getHeight());
    ASSERT_WITH_MESSAGE(pAttributesBackground == nullptr, SDL_GetError());
    ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, pAttributesBackground) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_RenderClear(pRenderer) != 0, SDL_GetError())

    ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(pAttributesBackground, SDL_BLENDMODE_BLEND) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(pAttributesBackground, 255) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_RenderCopy(pRenderer, background->getTexture(), nullptr, nullptr) != 0, SDL_GetError())

    int                            w, h; // Commonly used
    int                            row     = {};
    const int                      spacing = 4.0f;
    SDL_FRect                      pos{ 20.0f, 20.0f, 0, 0 };
    //Drawing all the texts
    const std::vector<std::string> attributes = { "Vitality", "Stamina", "Strength", "Dexterity", "Intelligence", "Luck" };
    for (const auto& attribute : attributes) {
        // Generate the text
        auto text = font->generateSentence(attribute, SDL_Color{ 0, 0, 0, 255 });
        ASSERT_WITH_MESSAGE(SDL_QueryTexture(text, nullptr, nullptr, &w, &h) != 0, SDL_GetError());
        if (row != 0)
            pos.y += static_cast<float>(spacing + h);   //First row shall be placed at start position
        pos.w = static_cast<float>(w);
        pos.h = static_cast<float>(h);
        SDL_RenderCopyF(pRenderer, text, nullptr, &pos);
        mAttributesLongestName = std::max(mAttributesLongestName, w);   //Store longest name
        row++;
    }
    // Reset renderer
    ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, nullptr) != 0, SDL_GetError());
}

std::vector<Graphics::typeDrawData>
UserInterface::getAttributes() {
    SDL_FRect              pos  = { 10, 10, 300, 160 };
    Graphics::typeDrawData data = { pAttributesBackground, nullptr, &pos };
    return std::vector<Graphics::typeDrawData>{ data };
}

}