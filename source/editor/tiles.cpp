#include <editor/editor.hpp>

namespace Editor {
void
Editor::uiTiles() {
    if (pVisualTile == nullptr || pLevelHeader == nullptr)
        return;
    for (int y = 0; y < pLevelHeader->MapSizeY; y++) {
        for (int x = 0; x < pLevelHeader->MapSizeX; x++) {
            int index = getIndex(x,y);
            if(pVisualTile[index]->first != nullptr){
                SDL_RenderTexture(pRenderer, pVisualTile[index]->first, nullptr, &pVisualTile[index]->second);
            }
        }
    }
}
}