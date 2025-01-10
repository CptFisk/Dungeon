#include <error.hpp>
#include <graphics/graphics.hpp>
#include <ui/userInterface.hpp>
#include <utility/string.hpp>
namespace Engine::UI {

void
UserInterface::calculateAttributes() {
    // First we clear the current UI if its already created
    auto& background = mAttributesDrawData.front();
    if (background.Texture)
        SDL_DestroyTexture(background.Texture);
    auto bgImage = GET_USERINTERFACE("Stats");
    auto font    = GET_TTF(DEFAULT_FONT);

    pAttributesBackground =
      SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, bgImage->getWidth(), bgImage->getHeight());
    ASSERT_WITH_MESSAGE(pAttributesBackground == nullptr, SDL_GetError());
    ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, pAttributesBackground) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_RenderClear(pRenderer) != 0, SDL_GetError())

    ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(pAttributesBackground, SDL_BLENDMODE_BLEND) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(pAttributesBackground, 255) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_RenderCopy(pRenderer, bgImage->getTexture(), nullptr, nullptr) != 0, SDL_GetError())

    int       w, h; // Commonly used
    int       row     = {};
    const int spacing = 4.0f;
    SDL_FRect pos{ 30.0f, 20.0f, 0, 0 };
    // Drawing all the texts
    const std::vector<std::string> attributes = { "Vitality", "Stamina", "Strength", "Dexterity", "Intelligence", "Luck" };
    for (const auto& attribute : attributes) {
        // Generate the text
        auto text = font->generateSentence(attribute, SDL_Color{ 224, 224, 224, 255 });
        ASSERT_WITH_MESSAGE(SDL_QueryTexture(text, nullptr, nullptr, &w, &h) != 0, SDL_GetError());
        if (row != 0)
            pos.y += static_cast<float>(spacing + h); // First row shall be placed at start position
        pos.w = static_cast<float>(w);
        pos.h = static_cast<float>(h);
        SDL_RenderCopyF(pRenderer, text, nullptr, &pos);
        mAttributesLongestName = std::max(mAttributesLongestName, w + 30); // Store longest name
        row++;
    }
    // Reset renderer
    ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, nullptr) != 0, SDL_GetError());

    const auto [x, y]    = calculateCenter();
    const auto uiCenterX = bgImage->getWidthF() / 2.0f;
    const auto uiCenterY = bgImage->getHeightF() / 2.0f;
    // Calculate top left position
    const auto topLeft = SDL_FPoint{ x - uiCenterX, y - uiCenterY };
    // Calculations
    background.Position->x = topLeft.x;
    background.Position->y = topLeft.y;
    background.Position->w = bgImage->getWidthF();
    background.Position->h = bgImage->getHeightF();
    background.Texture     = pAttributesBackground;
}

void
UserInterface::updateAttributes() {
    auto& background = mAttributesDrawData.back();
    if (pAttributesValues)
        SDL_DestroyTexture(pAttributesValues);
    ASSERT_WITH_MESSAGE(pAttributesBackground == nullptr, "Wrong call order, call calculateAttributes before")
    auto bgImage = GET_USERINTERFACE("Stats");
    auto font    = GET_TTF(DEFAULT_FONT);

    // Creating new base for graphics
    pAttributesValues =
      SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, bgImage->getWidth(), bgImage->getHeight());
    ASSERT_WITH_MESSAGE(pAttributesValues == nullptr, SDL_GetError());
    ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, pAttributesValues) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_RenderClear(pRenderer) != 0, SDL_GetError())

    ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(pAttributesValues, SDL_BLENDMODE_BLEND) != 0, SDL_GetError())
    ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(pAttributesValues, 255) != 0, SDL_GetError())

    int       w, h; // Commonly used
    const int spacing = 4.0f;
    SDL_FRect pos{ 30.0f + static_cast<float>(mAttributesLongestName), 20.0f, 0, 0 };

    for (int i = 0; i < 6; i++) {
        const auto playerStat = Utility::padLeft(std::to_string(mPlayerStats.at(i)), 2);
        const auto itemStat   = Utility::padRight(std::to_string(mItemStats.at(i)), 2);
        const auto result     = std::string().append(playerStat).append(" / ").append(itemStat);

        auto text = font->generateSentence(result, SDL_Color{ 224, 224, 224, 255 });
        ASSERT_WITH_MESSAGE(SDL_QueryTexture(text, nullptr, nullptr, &w, &h) != 0, SDL_GetError());
        if (i != 0)
            pos.y += static_cast<float>(spacing + h); // First row shall be placed at start position
        pos.w = static_cast<float>(w);
        pos.h = static_cast<float>(h);
        SDL_RenderCopyF(pRenderer, text, nullptr, &pos);
    }

    // Reset renderer
    ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, nullptr) != 0, SDL_GetError());

    const auto [x, y]    = calculateCenter();
    const auto uiCenterX = bgImage->getWidthF() / 2.0f;
    const auto uiCenterY = bgImage->getHeightF() / 2.0f;
    // Calculate top left position
    const auto topLeft = SDL_FPoint{ x - uiCenterX, y - uiCenterY };
    // Calculations
    background.Position->x = topLeft.x;
    background.Position->y = topLeft.y;
    background.Position->w = bgImage->getWidthF();
    background.Position->h = bgImage->getHeightF();
    background.Texture     = pAttributesValues;
}

std::vector<Graphics::typeDrawData>
UserInterface::getAttributes() const {
    return mAttributesDrawData;
}

}