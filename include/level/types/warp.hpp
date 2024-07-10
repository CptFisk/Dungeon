#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include <level/types/coordinate.hpp>

namespace Level::File{


struct typeWarpData{
    typeMapCoordinate Origin;
    typeMapCoordinate Destination;
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