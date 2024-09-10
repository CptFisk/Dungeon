#include <common/math.hpp>
#include <editor/editor.hpp>
#include <global.hpp>

namespace Editor {
void
Editor::uiTiles() {
    if (editorTiles.empty())
        return; // Break on empty

    const auto minX = std::max(INT((mOffset.X / -1.0f) / (16.0f * mScale.selectedScale) - 3.0f), 0);
    const auto minY = std::max(INT((mOffset.Y / -1.0f) / (16.0f * mScale.selectedScale) - 3.0f), 0);
    const auto maxX = std::min(minX + 40, MAP_WIDTH);
    const auto maxY = std::min(minY + 40, MAP_WIDTH);

    int  layer      = 0;
    bool layersLeft = false;
    do {
        if (layersLeft)
            layer++;

        layersLeft = false;
        for (int y = minY; y < maxY; y++) {
            for (int x = minX; x < maxX; x++) {
                const auto pos = Common::getIndex(x, y, MAP_WIDTH);
                // Check if valid position
                if (pos.has_value()) {
                    const auto& drawData = editorTiles[pos.value()]->getBaseDrawData();
                    if (INT(drawData.size() - 1) == layer) {
                        mPerspective->render(drawData[layer].Texture, drawData[layer].Viewport, drawData[layer].Position);
                    } else if (INT(drawData.size()) > layer) {
                        mPerspective->render(drawData[layer].Texture, drawData[layer].Viewport, drawData[layer].Position);
                        layersLeft = true;
                    }
                }
            }
        }
    } while (layersLeft);

    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {
            auto pos = Common::getIndex(x, y, MAP_WIDTH);
            if (pos.has_value()) {
                //Draw the top layer
                for(const auto& drawData : editorTiles[pos.value()]->getTopDrawData()){
                    mPerspective->render(drawData.Texture, drawData.Viewport, drawData.Position);
                }
                if (showNumbers) {
                    auto number = editorTiles[pos.value()]->getNumbers();
                    mPerspective->render(number.Texture, number.Viewport, number.Position);
                }
                if(showOverlay){
                    auto overlay = editorTiles[pos.value()]->getOverlay();
                    mPerspective->render(overlay.Texture, overlay.Viewport, overlay.Position);
                }
            }
        }
    }
}
}