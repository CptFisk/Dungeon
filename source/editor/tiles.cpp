#include <common/math.hpp>
#include <common/structures.hpp>
#include <editor/editor.hpp>

namespace Editor {
void
Editor::uiTiles() {
    const auto minX = std::max(static_cast<int>((mOffset.X / -1.0f) / (16.0f * mScale.ScaleX)), 0);
    const auto minY = std::max(static_cast<int>((mOffset.Y / -1.0f) / (16.0f * mScale.ScaleY)), 0);
    const auto maxX = std::min(minX + 16, static_cast<int>(fileHeader.Level.SizeX));
    const auto maxY = std::min(minY + 12, static_cast<int>(fileHeader.Level.SizeY));

    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {
            auto pos = Common::getIndex(x, y, fileHeader.Level.SizeX);
            if (pos.has_value()) {
                const int index = pos.value();
                // Draw all tiles
                for (auto visual : editorTiles[index].getTile()) {
                    mPerspective->render(visual.Texture, visual.Viewport, visual.Position);
                }
                if(showOverlay) {
                    auto overlay = visualOverlay[index];
                    mPerspective->render(overlay.getOverlay(), nullptr, &overlay.getPosition());
                }
                if(showNumbers) {
                    auto obj = visualOverlay[index];
                    auto number = obj.getNumber();
                    mPerspective->render(number.first, &number.second, &obj.getPosition());
                }
            }
        }
    }
    /*
     for(auto& [id, element] : visualOverlay){
         auto overlay = element.getOverlay();
         auto number = element.getNumber();
         mPerspective->render(overlay.first, nullptr, &overlay.second);
         mPerspective->render(number.first, &number.second, &overlay.second);    //Position is re-used

     }
     */
}
}