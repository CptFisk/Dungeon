#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <file/types/coordinate.hpp>

namespace File{

struct typeHeaderData {
    type3DMapCoordinate MapCoordinate;

    struct Colour {
        uint8_t BackgroundRed;   // RGB colour of background
        uint8_t BackgroundGreen; // RGB colour of background
        uint8_t BackgroundBlue;  // RGB colour of background
        Colour()
          : BackgroundRed(0)
          , BackgroundGreen(0)
          , BackgroundBlue(0){};
    } Colour;

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