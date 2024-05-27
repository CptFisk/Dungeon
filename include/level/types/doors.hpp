#pragma once
#include <cstdint>
#include <string>

namespace Level::File {
struct typeDoorsData {
    uint8_t     X;          // X-coordinate
    uint8_t     Y;          // Y-coordinate
    std::string Conditions; // Condition for open door

    typeDoorsData()
      : X{}
      , Y{}
      , Conditions{} {}
};

struct typeDoors{
    std::vector<typeDoors> Doors;
};

}