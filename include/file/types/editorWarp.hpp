#pragma once
#include <common/coordinates.hpp>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace File {

struct typeWarpData {
    Common::type2DMapCoordinate Origin;
    Common::type3DMapCoordinate Level;       // Level that contains the coordinate
    Common::type2DMapCoordinate Destination; // Destination on the level

    typeWarpData()
      : Origin{}
      , Level{}
      , Destination{} {}

    typeWarpData(const Common::type2DMapCoordinate& origin,
                 const Common::type3DMapCoordinate& level,
                 const Common::type2DMapCoordinate& destination)
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