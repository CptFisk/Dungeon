#pragma once
#include <cstdint>
#include <global.hpp>
#include <sstream>
#include <string>

namespace Common {
struct type3DMapCoordinate {
    uint8_t X;
    uint8_t Y;
    uint8_t Z;

    type3DMapCoordinate()
      : X(0)
      , Y(0)
      , Z(0) {}

    type3DMapCoordinate(const uint8_t& x, const uint8_t& y, const uint8_t& z)
      : X(x)
      , Y(y)
      , Z(z) {}

    bool operator==(const type3DMapCoordinate& other) const { return other.X == X && other.Y == Y && other.Z == Z; }

    bool operator!=(const type3DMapCoordinate& other) const { return other.X != X || other.Y != Y || other.Z != Z; }

    [[nodiscard]] std::string toString() const {
        std::ostringstream oss;
        oss << INT(X) << INT(Y) << INT(Z);
        return oss.str();
    }
};

struct type2DMapCoordinate {
    uint8_t X;
    uint8_t Y;

    type2DMapCoordinate()
      : X(0)
      , Y(0) {}

    type2DMapCoordinate(const uint8_t& x, const uint8_t& y)
      : X(x)
      , Y(y) {}

    bool operator==(const type2DMapCoordinate& other) const { return other.X == X && other.Y == Y; }

    bool operator!=(const type2DMapCoordinate& other) const { return other.X != X || other.Y != Y; }

    [[nodiscard]] std::string toString() const {
        std::ostringstream oss;
        oss << INT(X) << INT(Y);
        return oss.str();
    }
};
}