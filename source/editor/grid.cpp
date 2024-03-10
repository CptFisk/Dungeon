#include <editor/editor.hpp>

namespace Editor {
void
Editor::uiDrawGrid() {
    // Set line color
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    const auto offsetX = static_cast<int>(mOffset.X);
    const auto offsetY = static_cast<int>(mOffset.Y);
    const auto tileX   = 16.0f * mScale.ScaleX;
    const auto tileY   = 16.0f * mScale.ScaleY;
    const auto moduloX = static_cast<float>(fmod(mOffset.X, tileX));
    const auto moduloY = static_cast<float>(fmod(mOffset.Y, tileY));
    // Draw horizontal lines
    for (int i = 0; i <= 12; i++) {
        const auto y = static_cast<float>(i) * tileY + moduloY;
        SDL_RenderLine(pRenderer, 0.0, y, 800.0, y);
    }
    // Draw vertical lines
    for (int i = 0; i <= 16; i++) {
        const auto x = static_cast<float>(i) * tileX + moduloX;
        SDL_RenderLine(pRenderer, x, 0.0f, x, 600.0);
    }
}
}