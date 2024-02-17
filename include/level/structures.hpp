#pragma once
#include <cstdint>
namespace Level{
    struct LevelHeader{
        uint8_t HeaderVersion;
        char MapName[31];

        uint8_t BackgroundRed;
        uint8_t BackgroundGreen;
        uint8_t BackgroundBlue;
    };
}