#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace Level::File {
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
      , GraphicOpen("DoorOpenAnimation")
      , GraphicClosing("DoorCloseAnimation") {}
    typeDoorsData(const uint8_t& x, const uint8_t& y, const std::string& condition)
      : X(x)
      , Y(y)
      , GraphicOpen("DoorOpenAnimation")
      , GraphicClosing("DoorCloseAnimation") {}
    typeDoorsData(const uint8_t& x, const uint8_t& y, const std::string& condition, const std::string& open, const std::string& close)
      : X(x)
      , Y(y)
      , GraphicOpen(open)
      , GraphicClosing(close) {}
};

}