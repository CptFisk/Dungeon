#include <editor/editor.hpp>

namespace Editor {
void
Editor::uiDrawGrid() {
    const int maxX = SDL_MAX_UINT8;
    const int maxY = SDL_MAX_UINT8;
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    const int lineHeight = SDL_MAX_UINT8 * 16.0 * mScale.ScaleY;
    const int lineWidth = SDL_MAX_UINT8 * 16 * mScale.ScaleX;
    if (mShowGrid) {
        // Draw all vertical lines
        for (int i = 1; i < maxX; i++)
            SDL_RenderLine(pRenderer, i * (16.0 * mScale.ScaleX), 0.0, i * (16.0 * mScale.ScaleX), lineHeight);
        // Draw all horizontal lines
        for(int i = 1; i < maxY; i++)
            SDL_RenderLine(pRenderer, 0, i * (16.0 * mScale.ScaleY), lineWidth, i * (16.0 * mScale.ScaleY));
    }
}
}