#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

namespace Level::File{

struct typeWarpCoordinate{
    uint8_t X;  //X-coordinate
    uint8_t Y;  //Y-coordinate
};

struct typeWarpData{
    typeWarpCoordinate Origin;
    typeWarpCoordinate Destination;
    std::string Filename;
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