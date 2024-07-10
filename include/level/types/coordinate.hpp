#pragma once
#include <cstdint>
#include <global.hpp>
#include <sstream>
#include <string>

namespace Level::File {
struct typeMapCoordinate {
    uint8_t X;
    uint8_t Y;
    uint8_t Z;

    typeMapCoordinate()
      : X(0)
      , Y(0)
      , Z(0) {}

    typeMapCoordinate(const uint8_t& x, const uint8_t& y, const uint8_t& z)
      : X(x)
      , Y(y)
      , Z(z) {}

    bool operator==(const typeMapCoordinate& other) const { return other.X == X && other.Y == Y && other.Z == Z; }

    bool operator!=(const typeMapCoordinate& other) const { return other.X != X || other.Y != Y || other.Z != Z; }

    [[nodiscard]] std::string toString() const {
        std::ostringstream oss;
        oss << INT(X) << INT(Y) << INT(Z);
        return oss.str();
    }
};
}