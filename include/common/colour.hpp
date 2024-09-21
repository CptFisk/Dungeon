#pragma once
#include <cstdint>

namespace Common{
/**
 * @brief Definition of a colour structure
 */
struct typeColour {
    uint8_t BackgroundRed;   // RGB colour of background
    uint8_t BackgroundGreen; // RGB colour of background
    uint8_t BackgroundBlue;  // RGB colour of background
    typeColour()
      : BackgroundRed(0)
      , BackgroundGreen(0)
      , BackgroundBlue(0){};
};
}