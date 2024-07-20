#include <common/math.hpp>
#include <common/structures.hpp>
#include <editor/editor.hpp>
#include <global.hpp>

namespace Editor {
void
Editor::uiTiles() {
    if (editorTiles.empty())
        return; // Break on empty

    const auto minX = std::max(INT((mOffset.X / -1.0f) / (16.0f * mScale.factorX) - 3.0f), 0);
    const auto minY = std::max(INT((mOffset.Y / -1.0f) / (16.0f * mScale.factorY) - 3.0f), 0);
    const auto maxX = std::min(minX + 20, MAP_WIDTH);
    const auto maxY = std::min(minY + 16, MAP_WIDTH);

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
    /*
    if (showOverlay) {
        // Doors are drawn outside
        for (const auto& door : fileDoors) {
            SDL_FRect position = { FLOAT(door.X) * 16.0f * mScale.factorX,
                                   FLOAT(door.Y) * 16.0f * mScale.factorY,
                                   16.0f * mScale.factorX,
                                   16.0f * mScale.factorY };
            mPerspective->render(*GET_SDL("A89AE7"), nullptr, &position);
        }
        for (const auto warp : fileWarps) {
            SDL_FRect oPosition = {
                FLOAT(warp.Origin.X) * 16.0f * mScale.factorX,
                FLOAT(warp.Origin.Y) * 16.0f * mScale.factorY,
                16.0f * mScale.factorX,
                16.0f * mScale.factorY
            };
            SDL_FRect dPosition = {
                FLOAT(warp.Destination.X) * 16.0f * mScale.factorX,
                FLOAT(warp.Destination.Y) * 16.0f * mScale.factorY,
                16.0f * mScale.factorX,
                16.0f * mScale.factorY
            };
            mPerspective->render(*GET_SDL("CF2B0B"), nullptr, &oPosition);
            mPerspective->render(*GET_SDL("8CCFCD"), nullptr, &dPosition);
        }

        // Display player spawn
        mPerspective->render(*GET_SDL("0000FF"), nullptr, &mPlayerSpawn);
    }
     */
}
}