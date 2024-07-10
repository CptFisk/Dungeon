#pragma once
#include <cstdint>
#include <fstream>
#include <level/types/coordinate.hpp>
#include <string>
#include <vector>

namespace Level::File {

struct typeWarpData {
    typeMapCoordinate Origin;
    typeMapCoordinate Level;       // Level that contains the coordinate
    typeMapCoordinate Destination; // Destination on the level
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