#include <file/editorFile.hpp>
#include <file/types/editorAssets.hpp>
#include <file/types/editorDoor.hpp>
#include <file/types/editorTile.hpp>
#include <file/types/editorWarp.hpp>
#include <file/types/header.hpp>
#include <fstream>

namespace File {

void
writeEditorFile(const std::string& filename, const typeEditorFile& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Cant write to file");
    // Write header
    writeHeaderData(file, data.Header);
    writeAssetData(file, data.Assets);
    writeEditorTileData(file, data.Tiles);
    writeDoorData(file, data.Doors);
    writeWarpData(file, data.Warps);

    file.close();
}

typeEditorFile
readEditorFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("Cant load file: " + filename);
    typeHeaderData             header = {};
    typeAssets                 assets;
    typeEditorTiles            tiles(MAP_SIZE);
    std::vector<typeDoorsData> doors;
    std::vector<typeWarpData>  warps;

    // Read the size of how many assets is stored in the file
    readHeaderData(file, header);
    readAssetData(file, assets);
    readEditorTileData(file, tiles);
    readDoorData(file, doors);
    readWarpData(file, warps);

    file.close();
    // Generating response
    return typeEditorFile{ header, assets, tiles, doors, warps };
}

}