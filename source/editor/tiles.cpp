#include <common/math.hpp>
#include <common/structures.hpp>
#include <editor/editor.hpp>

namespace Editor {
void
Editor::uiTiles() {
    if(editorTiles.empty())
        return; //Break on empty

    const auto minX = std::max(static_cast<int>((mOffset.X / -1.0f) / (16.0f * mScale.factorX) - 1.0f), 0);
    const auto minY = std::max(static_cast<int>((mOffset.Y / -1.0f) / (16.0f * mScale.factorY) - 1.0f), 0);
    const auto maxX = std::min(minX + 20, static_cast<int>(fileHeader.Level.SizeX));
    const auto maxY = std::min(minY + 16, static_cast<int>(fileHeader.Level.SizeY));

    std::vector<int> indices; // Contains all the tiles

    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {
            auto pos = Common::getIndex(x, y, fileHeader.Level.SizeX);
            if (pos.has_value()) {
                indices.emplace_back(pos.value());
            }
        }
        size_t maxSize = 0;
        for (const auto& index : indices) {
            maxSize = std::max(maxSize, editorTiles[index].getTile().size()); // Selecting the biggest value
        }

        for (int i = 0; i < maxSize; i++) {
            for (const auto& index : indices) {
                if (index < editorTiles.size() && i < editorTiles[index].getTile().size()) {
                    auto element = editorTiles[index].getTile()[i];
                    mPerspective->render(element.Texture, element.Viewport, element.Position);
                }
            }
        }

        //Show overlay's
        for(const auto& index: indices){
            auto visual = visualOverlay[index];
            if(showNumbers){
                auto number = visual.getNumber();
                mPerspective->render(number.first, &number.second, &visual.getPosition());
            }
            if(showOverlay){
                mPerspective->render(visual.getOverlay(), nullptr, &visual.getPosition());
            }
        }
    }
}
}