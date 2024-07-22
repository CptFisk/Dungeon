#pragma once
#include <bitset>

namespace Utility{
template<std::size_t N>
constexpr bool
isAnyBitSet(const std::bitset<N>& bitset, const std::bitset<N> mask){
    return (bitset & mask).any();
}

template<std::size_t N>
constexpr void resetBits(std::bitset<N>& bitset, const std::bitset<N> mask){
    bitset &= ~mask;
}
}