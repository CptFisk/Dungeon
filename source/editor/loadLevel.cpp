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
    mEdges.emplace_back(GET_SDL("FF0000"), SDL_FRect{ leftX, topY, tileSizeX, verticalLength });      // Left
    mEdges.emplace_back(GET_SDL("FF0000"), SDL_FRect{ rightX, topY, tileSizeX, verticalLength });     // Right
    mEdges.emplace_back(GET_SDL("FF0000"), SDL_FRect{ leftX, topY, horizontalLength, tileSizeY });    // top
    mEdges.emplace_back(GET_SDL("FF0000"), SDL_FRect{ leftX, bottomY, horizontalLength, tileSizeY }); // bottom

    // Creating the map
    editorTiles.clear();
    visualOverlay.clear();
    int pos = 0;
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            const auto tile = tiles.Tiles[pos]; // To keep name short
            // Generating both tiles and visual overlay
            editorTiles.emplace_back(Level::Tile(x, y, mScale));
            visualOverlay[pos] = VisualTile(x, y, GET_SIMPLE("NumbersWhite"), mScale);
            for (const auto id : tile.Id) {
                const auto val     = static_cast<int>(id);
                auto       texture = GET_SIMPLE(data.Assets.Assets[val]); // Assets to use
                editorTiles[pos].addData(texture.Texture, texture.getRandomView(), texture.Width, texture.Height, mScale);
                visualOverlay[pos].incrementCounter(); // Count up
                mLevelCoords.emplace(x,y);
            }
            pos++;
        }
    }
    mMapLoaded = true;
}
}