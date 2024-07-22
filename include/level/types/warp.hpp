#pragma once
#include <cstdint>
#include <fstream>
#include <level/types/coordinate.hpp>
#include <string>
#include <vector>

namespace Level {

struct typeWarpData {
    type2DMapCoordinate Origin;
    type3DMapCoordinate Level;       // Level that contains the coordinate
    type2DMapCoordinate Destination; // Destination on the level

    typeWarpData()
      : Origin{}
      , Level{}
      , Destination{} {}

    typeWarpData(const type2DMapCoordinate& origin, const type3DMapCoordinate& level, const type2DMapCoordinate& destination)
      : Origin(origin)
      , Level(level)
      , Destination(destination) {}
};

/**
 * @brief Read warps from a filestream
 */
void
readWarpData(std::ifstream& file, std::vector<typeWarpData>& data);

/**
 * @brief Write warps to a filestream
 */
void
writeWarpData(std::ofstream& file, const std::vector<typeWarpData>& data);

}