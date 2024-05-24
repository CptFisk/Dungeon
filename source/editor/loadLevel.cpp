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
    fileTiles  = tiles;

    // Clear edges and then create them
    //  Position for edges
    const auto sizeX = fileHeader.Level.SizeX;
    const auto sizeY = fileHeader.Level.SizeY;

    const auto leftX            = -16.0f * mScale.factorX;
    const auto rightX           = 16.0f * mScale.factorX * static_cast<float>(sizeX);
    const auto topY             = -16.0f * mScale.factorY;
    const auto bottomY          = 16.0f * mScale.factorY * static_cast<float>(sizeY);
    const auto tileSizeX        = 16.0f * mScale.factorX;
    const auto tileSizeY        = 16.0f * mScale.factorY;
    const auto verticalLength   = tileSizeX * (static_cast<float>(sizeY) + 2.0f);
    const auto horizontalLength = tileSizeY * (static_cast<float>(sizeX) + 2.0f);
    // Adding some visuals so we don't paint outside
    mEdges.clear();
    // Creating the map
    editorTiles.clear();
    visualOverlay.clear();
    int pos = 0;
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            const auto tile = tiles.Tiles[pos]; // To keep name short
            // Generating both tiles and visual overlay
            editorTiles.emplace_back(Tile(x, y, mScale));
            visualOverlay[pos] = VisualTile(x, y, GET_SIMPLE("NumbersWhite"), mScale);
            for (const auto id : tile.Id) {
                const auto val     = static_cast<int>(id);
                auto       texture = GET_SIMPLE(data.Assets.Assets[val]); // Assets to use
                editorTiles[pos].addData(texture.Texture, texture.getRandomView(), texture.Width, texture.Height, mScale);
                visualOverlay[pos].incrementCounter(); // Count up
                mLevelCoords.emplace(x,y);
            }
            if((tile.Type & static_cast<uint8_t>(Level::File::TileType::WALL)) != 0) {
                visualOverlay[pos].newOverlay(GET_SDL("87ED17"));
            }
            if((tile.Type & static_cast<uint8_t>(Level::File::TileType::OBSTACLE)) != 0) {
                visualOverlay[pos].newOverlay(GET_SDL("1D35FA"));
            }
            pos++;
        }
    }
    //Adding player spawn
    mPlayerSpawn.x = static_cast<float>(fileHeader.Level.PlayerX) * 16.0f * mScale.factorX;
    mPlayerSpawn.y = static_cast<float>(fileHeader.Level.PlayerY) * 16.0f * mScale.factorY;
    mPlayerSpawn.w = 16.0f *mScale.factorX;
    mPlayerSpawn.h = 16.0f *mScale.factorY;

    mMapLoaded = true;
}
}