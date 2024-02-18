#include <editor/editor.hpp>

namespace Editor {
void
Editor::uiDrawGrid() {
    const int maxX = SDL_MAX_UINT8;
    const int maxY = SDL_MAX_UINT8;
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    const int lineHeight = SDL_MAX_UINT8 * 16.0 * mScale.ScaleY;
    const int lineWidth  = SDL_MAX_UINT8 * 16 * mScale.ScaleX;
    if (mShowGrid) {
        // Draw all vertical lines
        for (int i = 1; i < maxX; i++)
            SDL_RenderLine(pRenderer, i * (16.0 * mScale.ScaleX), 0.0, i * (16.0 * mScale.ScaleX), lineHeight);
        // Draw all horizontal lines
        for (int i = 1; i < maxY; i++)
            SDL_RenderLine(pRenderer, 0, i * (16.0 * mScale.ScaleY), lineWidth, i * (16.0 * mScale.ScaleY));

        // Print numbers
        for (int y = 0; y < 12; y++) {
            for (int x = 0; x < 16; x++) {

                const std::string name    = std::to_string(x) + "," + std::to_string(y);
                auto              texture = mGraphics->getTexture(name);
                int               height;
                int               width;

                SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
                SDL_FRect position = { x * 16 * mScale.ScaleX + static_cast<float>(width / 2),
                                       y * 16 * mScale.ScaleY+ static_cast<float>(height / 2),
                                       static_cast<float>(width),
                                       static_cast<float>(height) };
                SDL_RenderTexture(pRenderer, texture, nullptr, &position);
            }
        }
    }
}
}