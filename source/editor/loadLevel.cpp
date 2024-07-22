#include <editor/editor.hpp>

namespace Editor {
/**
 * @brief This is not equal to the class Level that normally handles the tiles inside the game.
 * @brief The reason for this is that the editor handle so much more than just a normal tile drawing.
 */
void
Editor::loadLevel(const Level::typeLevelData& data) {
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
    for (int y = 0; y < MAP_WIDTH; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            const auto tile = tiles.Tiles[pos]; // To keep name short
            if(pos >= MAP_SIZE){
                std::cout << "FAILURE";
            }
            // Generating both tiles and visual overlay
            editorTiles.push_back(new Tile(x, y, mScale, *GET_SIMPLE("NumbersWhite"), pRenderer));
            for (const auto& id : tile.Base) {
                if(id <= assets.Assets.size()) {
                    const auto asset           = data.Assets.Assets[INT(id)];
                    animationValuesBase[asset] = editorTiles[pos]->addData(asset, fileAssets, mGraphics, false);
                    mLevelCoords.emplace(x, y);
                }
            }
            for (const auto& id : tile.Top) {
                const auto asset          = data.Assets.Assets[INT(id)];
                animationValuesTop[asset] = editorTiles[pos]->addData(asset, fileAssets, mGraphics, true);
                editorTiles[pos]->addOverlay(*GET_SDL(getMouseColorCode(Mouse::TOP_LAYER)));
                mLevelCoords.emplace(x, y);
            }
            if (tile.Type.test(Level::TileType::WALL)){
                editorTiles[pos]->addType(Level::TileType::WALL, *GET_SDL(getMouseColorCode(Mouse::WALL)));
            }
            if (tile.Type.test(Level::TileType::OBSTACLE)){
                editorTiles[pos]->addType(Level::TileType::OBSTACLE, *GET_SDL(getMouseColorCode(Mouse::OBSTACLE)));
            }
            if (tile.Type.test(Level::TileType::UP)) {
                editorTiles[pos]->addType(Level::TileType::UP, *GET_SDL(getMouseColorCode(Mouse::UP)));
            }
            if (tile.Type.test(Level::TileType::DOWN)) {
                editorTiles[pos]->addType(Level::TileType::DOWN, *GET_SDL(getMouseColorCode(Mouse::DOWN)));
            }
            pos++;
        }
    }

    mMapLoaded = true;
}
}