#include <editor/editor.hpp>

namespace Editor {
/**
 * @brief This is not equal to the class Level that normally handles the tiles inside the game.
 * @brief The reason for this is that the editor handle so much more than just a normal tile drawing.
 */
void
Editor::loadLevel(const Level::File::typeLevelData& data) {
    const auto header = data.Header;
    const auto assets = data.Assets;
    const auto tiles  = data.Tiles;

    fileHeader = header;
    fileAssets = assets;
    fileDoors  = data.Doors;
    fileWarps  = data.Warps;

    // Adding some visuals so we don't paint outside
    mEdges.clear();
    // Creating the map
    for (auto& tile : editorTiles) {
        delete tile;
    }
    editorTiles.clear();

    int pos = 0;
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            const auto tile = tiles.Tiles[pos]; // To keep name short
            // Generating both tiles and visual overlay
            editorTiles.push_back(new Tile(x, y, mScale, *GET_SIMPLE("NumbersWhite"), pRenderer));
            for (const auto& id : tile.Base) {
                const auto asset       = data.Assets.Assets[INT(id)];
                animationValues[asset] = editorTiles[pos]->addData(asset, fileAssets, mGraphics, false);
                mLevelCoords.emplace(x, y);
            }
            for (const auto& id : tile.Top) {
                const auto asset       = data.Assets.Assets[INT(id)];
                animationValues[asset] = editorTiles[pos]->addData(asset, fileAssets, mGraphics, true);
                mLevelCoords.emplace(x, y);
            }
            if ((tile.Type & UINT8(Level::File::TileType::WALL)) != 0) {
                editorTiles[pos]->addType(Level::File::TileType::WALL, *GET_SDL(getMouseColorCode(Mouse::WALL)));
            }
            if ((tile.Type & UINT8(Level::File::TileType::OBSTACLE)) != 0) {
                editorTiles[pos]->addType(Level::File::TileType::OBSTACLE, *GET_SDL(getMouseColorCode(Mouse::OBSTACLE)));
            }

            pos++;
        }
    }

    mMapLoaded = true;
}
}