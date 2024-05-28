#pragma once
#include <cstdint>
#include <string>

namespace Level::File {
struct typeDoorsData {
    uint8_t     X;         // X-coordinate
    uint8_t     Y;         // Y-coordinate
    std::string Condition; // Condition for open door

    typeDoorsData()
      : X{}
      , Y{}
      , Condition{} {}
    typeDoorsData(const uint8_t& x, const uint8_t& y, const std::string& condition)
      : X(x)
      , Y(y)
      , Condition(condition) {}
};

struct typeDoors {
    std::vector<typeDoorsData> Doors;
};

}