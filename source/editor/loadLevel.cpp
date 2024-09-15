#include <editor/editor.hpp>
#include <monster/definition.hpp>
#include <utility/bits.hpp>

namespace Editor {
/**
 * @brief This is not equal to the class Level that normally handles the tiles inside the game.
 * @brief The reason for this is that the editor handle so much more than just a normal tile drawing.
 */
void
Editor::loadLevel(const File::typeEditorFile& data) {
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
            if (pos >= MAP_SIZE) {
                std::cout << "FAILURE";
            }
            // Generating both tiles and visual overlay
            editorTiles.push_back(new Tile(x, y, mScale, GET_FONT("8bit16"), pRenderer));
            for (const auto& id : tile.Base) {
                if (id <= assets.Assets.size()) {
                    const auto asset           = data.Assets.Assets[INT(id)];
                    animationValuesBase[asset] = editorTiles[pos]->addData(asset, fileAssets, mGraphics, false);
                    mLevelCoords.emplace(x, y);
                }
            }
            for (const auto& id : tile.Top) {
                const auto asset          = data.Assets.Assets[INT(id)];
                animationValuesTop[asset] = editorTiles[pos]->addData(asset, fileAssets, mGraphics, true);
                editorTiles[pos]->addOverlay(GET_GENERATED(getMouseColorCode(Mouse::TOP_LAYER)));
                mLevelCoords.emplace(x, y);
            }
            if (Utility::isAnyBitSet(tile.Type, std::bitset<32>(LIGHT_BITS))) {
                auto  shape  = static_cast<LightningShape>(Utility::getSetBit(tile.Type, std::bitset<32>(LIGHT_SHAPE)));
                auto colour = static_cast<LightningColour>(Utility::getSetBit(tile.Type, std::bitset<32>(LIGHT_COLOUR)));
                auto   size   = static_cast<LightningSize>(Utility::getSetBit(tile.Type, std::bitset<32>(LIGHT_SIZE)));
                editorTiles[pos]->addLightning(shape, colour, size);
                editorTiles[pos]->addOverlay(GET_GENERATED(getMouseColorCode(Mouse::LIGHTNING)));
            }
            if (tile.Type.test(File::TileType::WALL)) {
                editorTiles[pos]->addType(File::TileType::WALL, GET_GENERATED(getMouseColorCode(Mouse::WALL)));
            }
            if (tile.Type.test(File::TileType::OBSTACLE)) {
                editorTiles[pos]->addType(File::TileType::OBSTACLE, GET_GENERATED(getMouseColorCode(Mouse::OBSTACLE)));
            }
            if (tile.Type.test(File::TileType::UP)) {
                editorTiles[pos]->addType(File::TileType::UP, GET_GENERATED(getMouseColorCode(Mouse::UP)));
            }
            if (tile.Type.test(File::TileType::DOWN)) {
                editorTiles[pos]->addType(File::TileType::DOWN, GET_GENERATED(getMouseColorCode(Mouse::DOWN)));
            }
            if (Utility::isAnyBitSet(tile.Type, std::bitset<32>(MONSTER_BITS))) {
                const auto monsterId = Utility::getBitValue<32, int>(tile.Type, 10, 17);
                const auto texture   = GET_ANIMATED(Monster::monsters[monsterId].DefaultImage);
                if (texture != nullptr) {
                    editorTiles[pos]->addMonster(monsterId, texture->getTexture(), texture->getViewports().front());
                }
            }
            pos++;
        }
    }

    mMapLoaded = true;
}
}