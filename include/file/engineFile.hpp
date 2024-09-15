#pragma once
#include <cstdint>
#include <vector>

namespace Level{
    struct typeMapData{
        long unsigned int Size;
        std::vector<char> Data;
    };

    struct typeEngineFile{
        uint8_t BottomSize;
        std::vector<typeMapData> Bottom;
    };
}