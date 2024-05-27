#pragma once
#include <cstdint>
#include <string>

namespace Level::File {
struct typeDoors {
    uint8_t     X;          // X-coordinate
    uint8_t     Y;          // Y-coordinate
    std::string Conditions; // Condition for open door

    typeDoors()
      : X{}
      , Y{}
      , Conditions{} {}
};
}