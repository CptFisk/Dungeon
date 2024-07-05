#pragma once
#include <SDL.h>
#include <cstdint>
#include <level/types/assets.hpp>
#include <level/types/door.hpp>
#include <level/types/header.hpp>
#include <level/types/spawn.hpp>
#include <level/types/tile.hpp>
#include <level/types/warp.hpp>
#include <string>
#include <vector>
#include <optional>

namespace Level::File {

struct typeLevelData {
    typeHeaderData             Header;
    typeAssets                 Assets;
    typeTiles                  Tiles;
    std::vector<typeDoorsData> Doors;
    std::vector<typeWarpData>  Warps;
    typeSpawn                  Spawns;
    typeLevelData(typeHeaderData              header,
                  typeAssets                  assets,
                  typeTiles                   tiles,
                  std::vector<typeDoorsData>& doors,
                  std::vector<typeWarpData>&  warps,
                  typeSpawn                   spawns)
      : Header(header)
      , Assets(std::move(assets))
      , Tiles(std::move(tiles))
      , Doors(std::move(doors))
      , Warps(std::move(warps))
      , Spawns(spawns){};
};

/**
 * @brief Write the current struct to a file
 * @param filename Name of the file
 * @param data Data structure
 */
void
writeLevelDataToFile(const std::string& filename, const typeLevelData& data);

/**
 * @brief Load a file and return a map
 * @param filename
 * @return Pointer to the map
 */
typeLevelData
readLevelData(const std::string& filename);


}