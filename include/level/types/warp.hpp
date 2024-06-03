#pragma once
#include <vector>
#include <string>
#include <cstdint>

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
}