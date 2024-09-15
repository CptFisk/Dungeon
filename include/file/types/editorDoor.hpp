#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace File {
struct typeDoorsData {
    uint8_t     X;              // X-coordinate
    uint8_t     Y;              // Y-coordinate
    std::string Condition;      // Condition for open door
    std::string GraphicOpen;    // Graphic used for opening door
    std::string GraphicClosing; // Graphic used for closing door

    typeDoorsData()
      : X{}
      , Y{}
      , Condition{}
      , GraphicOpen("VillageDoorBrownOpenAnimation")
      , GraphicClosing("VillageDoorBrownCloseAnimation") {}
    typeDoorsData(const uint8_t& x, const uint8_t& y, const std::string& condition)
      : X(x)
      , Y(y)
      , GraphicOpen("VillageDoorBrownOpenAnimation")
      , GraphicClosing("VillageDoorBrownCloseAnimation") {}
    typeDoorsData(const uint8_t& x, const uint8_t& y, const std::string& condition, const std::string& open, const std::string& close)
      : X(x)
      , Y(y)
      , GraphicOpen(open)
      , GraphicClosing(close) {}
};

/**
 * @brief Read doors from a filestream
 */
void
readDoorData(std::ifstream& file, std::vector<typeDoorsData>& data);

/**
 * @brief Write doors to a filestream
 */
void
writeDoorData(std::ofstream& file, const std::vector<typeDoorsData>& data);
}