#include <error.hpp>
#include <global.hpp>
#include <ui/textbox.hpp>
#include <utility/math.hpp>

namespace Engine::UI {

Textbox::Textbox(SDL_Renderer*& renderer, Common::typeScale& scale)
  : pRenderer(renderer)
  , mScale(scale)
  , mTextures{}
  , mElements{}
  , mPositions{}
  , mTextboxes{} {}

Textbox::~Textbox() {
    for (auto texture : mTextures) {
        SDL_DestroyTexture(texture);
    }
}

void
Textbox::generateBoxes() {
    // Clear all old textures
    for (auto texture : mTextures) {
        if (texture)
            SDL_DestroyTexture(texture);
    }

    for (auto e : mElements) {
        if (e.Graphics[0] != nullptr && e.Graphics[1] != nullptr && e.Graphics[2] != nullptr) {
            ASSERT_WITH_MESSAGE(!Utility::allEqual(e.Graphics[0]->getHeight(), e.Graphics[1]->getHeight(), e.Graphics[1]->getHeight()),
                                "All texture need same height")
            // Calculate dimensions
            const auto width =
              (mScale.windowWidthF / mScale.selectedScale) - e.Graphics[0]->getMarginLeftF() - e.Graphics[2]->getMarginLeftF();
            // Calculate the dimension the center piece need
            e.Graphics[1]->setWidth(width - e.Graphics[0]->getWidthF() - e.Graphics[2]->getWidthF());
            const auto height = e.Graphics[0]->getHeight();

            auto texture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, INT(width), height);
            ASSERT_WITH_MESSAGE(texture == nullptr, SDL_GetError())
            ASSERT_WITH_MESSAGE(texture == nullptr, SDL_GetError())
            ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, texture) != 0, SDL_GetError())
            ASSERT_WITH_MESSAGE(SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0) != 0, SDL_GetError())
            ASSERT_WITH_MESSAGE(SDL_RenderClear(pRenderer) != 0, SDL_GetError())

            ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) != 0, SDL_GetError())
            ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(texture, 255) != 0, SDL_GetError())

            // Render all objects to the new graphics
            int offset = 0;
            for (auto box : e.Graphics) {
                auto dest = SDL_Rect{ offset, 0, box->getWidth(), height };
                SDL_RenderCopy(pRenderer, box->getTexture(), nullptr, &dest);
                offset += box->getWidth();
            }
            // Saving all progress

            mTextures[e.Size]  = texture; // Save texture so we can clear it later
            mPositions[e.Size] = { e.Graphics[0]->getMarginLeftF(),
                                   FLOAT(INT(FLOAT(mScale.windowHeight) / mScale.selectedScale) - e.Graphics[0]->getMarginBottomF()),
                                   width,
                                   e.Graphics[0]->getHeightF() };
            mTextboxes[e.Size] = { texture, nullptr, &mPositions[e.Size] };
            ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, nullptr) != 0, SDL_GetError())
        }
    }
}

void
Textbox::addElements(const Engine::UI::TextboxSize&  size,
                     Graphics::UserInterfaceTexture* start,
                     Graphics::UserInterfaceTexture* center,
                     Graphics::UserInterfaceTexture* end) {
    mElements[size] = { { start, center, end }, size };
}

Graphics::typeDrawData
Textbox::getTextbox(const TextboxSize& size) {
    return mTextboxes[size];
}
}