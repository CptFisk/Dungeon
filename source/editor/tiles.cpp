#include <editor/editor.hpp>
#include <common/math.hpp>

namespace Editor {
void
Editor::uiTiles() {
    if (pVisualTile == nullptr || pLevelHeader == nullptr)
        return;
    for (int y = 0; y < pLevelHeader->Level.SizeY; y++) {
        for (int x = 0; x < pLevelHeader->Level.SizeX; x++) {
            int index = Common::getIndex(x,y, pLevelHeader);
            if(pVisualTile[index]->first != nullptr){
                SDL_RenderTexture(pRenderer, pVisualTile[index]->first, nullptr, &pVisualTile[index]->second);
            }
        }
    }
}
}