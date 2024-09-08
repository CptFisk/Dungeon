#include <editor/editor.hpp>

namespace Editor {
void
Editor::uiDrawGrid() {
    if(!showGrid)
        return;
    // Set line color
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    const auto tileX   = 16.0f * mScale.selectedScale;
    const auto tileY   = 16.0f * mScale.selectedScale;
    const auto moduloX = static_cast<float>(fmod(mOffset.X, tileX));
    const auto moduloY = static_cast<float>(fmod(mOffset.Y, tileY));
    // Draw horizontal lines
    for (int i = 0; i <= 12; i++) {
        const auto y = static_cast<float>(i) * tileY + moduloY;
        SDL_RenderDrawLineF(pRenderer, 0.0f, y, mScale.windowWidthF, y);
    }
    // Draw vertical lines
    for (int i = 0; i <= 16; i++) {
        const auto x = static_cast<float>(i) * tileX + moduloX;
        SDL_RenderDrawLineF(pRenderer, x, 0.0f, x, mScale.windowWidthF);
    }
}
}