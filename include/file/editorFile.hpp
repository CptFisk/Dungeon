#pragma once
#include <SDL.h>
#include <cstdint>
#include <file/types/editorAssets.hpp>
#include <file/types/editorDoor.hpp>
#include <file/types/editorTile.hpp>
#include <file/types/editorWarp.hpp>
#include <file/types/header.hpp>
#include <optional>
#include <string>
#include <vector>

namespace File {

/**
 * @brief Structure used for editor files
 */
struct typeEditorFile {
    typeHeaderData             Header;
    typeAssets                 Assets;
    typeTiles                  Tiles;
    std::vector<typeDoorsData> Doors;
    std::vector<typeWarpData>  Warps;
    typeEditorFile(typeHeaderData              header,
                   typeAssets                  assets,
                   typeTiles                   tiles,
                   std::vector<typeDoorsData>& doors,
                   std::vector<typeWarpData>&  warps)
      : Header(std::move(header))
      , Assets(std::move(assets))
      , Tiles(std::move(tiles))
      , Doors(std::move(doors))
      , Warps(std::move(warps)) {}
};

/**
 * @brief Write data to a editor file, so it can be edited later
 * @param filename Name of the file
 * @param data Data structure
 */
void
writeEditorFile(const std::string& filename, const typeEditorFile& data);

/**
 * @brief Load a editor file and return structures into the level editor
 * @param filename
 * @return Pointer to the map
 */
typeEditorFile
readEditorFile(const std::string& filename);

}