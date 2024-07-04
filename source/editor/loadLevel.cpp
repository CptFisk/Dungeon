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

    // Clear edges and then create them
    //  Position for edges
    const auto sizeX = fileHeader.Level.SizeX;
    const auto sizeY = fileHeader.Level.SizeY;

    // Adding some visuals so we don't paint outside
    mEdges.clear();
    // Creating the map
    for (auto& tile : editorTiles) {
        delete tile;
    }
    editorTiles.clear();

    int pos = 0;
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            const auto tile = tiles.Tiles[pos]; // To keep name short
            // Generating both tiles and visual overlay
            editorTiles.push_back(new Tile(x, y, mScale, *GET_SIMPLE("NumbersWhite"), pRenderer));
            for (const auto& id : tile.Base) {
                if (editorTiles[pos]->addData(data.Assets.Assets[INT(id)], fileAssets, mGraphics, false))
                    mLevelCoords.emplace(x, y);
            }
            for(const auto& id : tile.Top){
                if (editorTiles[pos]->addData(data.Assets.Assets[INT(id)], fileAssets, mGraphics, true))
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
    // Adding player spawn
    mPlayerSpawn.x = static_cast<float>(fileHeader.Level.PlayerX) * 16.0f * mScale.factorX;
    mPlayerSpawn.y = static_cast<float>(fileHeader.Level.PlayerY) * 16.0f * mScale.factorY;
    mPlayerSpawn.w = 16.0f * mScale.factorX;
    mPlayerSpawn.h = 16.0f * mScale.factorY;

    mMapLoaded = true;
}
}