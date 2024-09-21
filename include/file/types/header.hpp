#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <common/colour.hpp>
#include <common/coordinates.hpp>

namespace File{

struct typeHeaderData {
    Common::type3DMapCoordinate MapCoordinate;
    Common::typeColour Colour;

    std::vector<std::string> OnLoad;
    std::vector<std::string> OnExit;
};

/**
 * @brief Read header from a filestream
 */
void
readHeaderData(std::ifstream& file, typeHeaderData& data);

/**
 * @brief Write header to a filestream
 */
void
writeHeaderData(std::ofstream& file, const typeHeaderData& data);
}