#include <editor/editor.hpp>

namespace Editor{
void
Editor::uiDrawGrid() {
    const int maxX = SDL_MAX_UINT8;
    const int maxY = SDL_MAX_UINT8;
    SDL_SetRenderDrawColor(pRenderer, 255,255,255, SDL_ALPHA_OPAQUE);
    if(mShowGrid){
        //Draw all vertical lines
        for(int i = 1; i < maxX; i++){
            SDL_RenderLine(pRenderer, i * (16.0*mScale.ScaleX), 0.0, i * (16.0*mScale.ScaleX), 800.0);
        }


    }
}
}