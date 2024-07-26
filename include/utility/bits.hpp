#pragma once
#include <bitset>

namespace Utility {
template<std::size_t N>
constexpr bool
isAnyBitSet(const std::bitset<N>& bitset, const std::bitset<N>& mask) {
    return (bitset & mask).any();
}

template<std::size_t N>
constexpr void
resetBits(std::bitset<N>& bitset, const std::bitset<N>& mask) {
    bitset &= ~mask;
}

template<std::size_t N>
constexpr int
getSetBit(const std::bitset<N>& bitset, const std::bitset<N>& mask) {
    std::bitset<N> data = bitset & mask;
    if (data.count() != 1)
        return 0;
    for (int i = 0; i < N; ++i) {
        if (data.test(i))
            return i;
    }
    return 0;
}
}