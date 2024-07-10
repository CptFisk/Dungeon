#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include <global.hpp>

namespace Level::File{
struct typeMapCoordinate{
    uint8_t X;
    uint8_t Y;
    uint8_t Z;

    bool operator==(const typeMapCoordinate& other) const{
        return other.X == X && other.Y == Y && other.Z == Z;
    }

    bool operator !=(const typeMapCoordinate& other) const{
        return other.X != X || other.Y != Y || other.Z != Z;
    }

    std::string toString() const{
        std::ostringstream oss;
        oss << INT(X) << INT(Y) << INT(Z);
        return oss.str();
    }
};
}