#include <editor/editor.hpp>
#include <common/math.hpp>

namespace Editor {
void
Editor::uiTiles() {
    for(auto& [id, tile] : tiles){
        for(auto visual : tile.getTile())
            mPerspective->render(visual.Texture, visual.Viewport, visual.Position);
    }

    for(auto& [id, overlay] : visualOverlay){
        auto data = overlay.getOverlay();
        mPerspective->render(data.first, nullptr, &data.second);
    }
}
}