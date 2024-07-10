#pragma once
#include <cstdint>

namespace Level::File{
struct typeMapCoordinate{
    uint8_t X;
    uint8_t Y;
    uint8_t Z;

    bool operator==(const typeMapCoordinate& other) const{
        return other.X == X && other.Y == Y && other.Z == Z;
    }
};
}