#include <editor/editor.hpp>
#include <common/math.hpp>

namespace Editor {
void
Editor::uiTiles() {
    for(auto& [id, tile] : tiles){
        for(auto visual : tile.getTile())
            mPerspective->render(visual.Texture, visual.Viewport, visual.Position);
    }

    for(auto& [id, element] : visualOverlay){
        auto overlay = element.getOverlay();
        auto number = element.getNumber();
        mPerspective->render(overlay.first, nullptr, &overlay.second);
        mPerspective->render(number.first, &number.second, &overlay.second);    //Position is re-used

    }
}
}