#pragma once
#include <bitset>

namespace Utility {

/**
 * @brief Evaluate if any bit is set within the current mask when applied to the bitset.
 * @tparam N Size of the bitset
 * @param bitset Value that shall be evaluated
 * @param mask Mask
 * @return True if any bit it set
 */
template<std::size_t N>
constexpr bool
isAnyBitSet(const std::bitset<N>& bitset, const std::bitset<N>& mask) {
    return (bitset & mask).any();
}

/**
 * @brief Reset all bits within the current mask
 * @tparam N Size of the bitset
 * @param bitset Reference to the current bitset
 * @param mask Mask that will be used to reset the bits
 * @return No return
 */
template<std::size_t N>
constexpr void
resetBits(std::bitset<N>& bitset, const std::bitset<N>& mask) {
    bitset &= ~mask;
}

/**
 * @brief Return the position that a bit is set on. If multiple bits is set within the mask, the function will return 0
 * @tparam N Size of the bitmask
 * @param bitset Bitset that shall be evaluated
 * @param mask Mask to select which bit for evaluating
 * @return Position of the bit, 0 means not found or more than 1.
 */
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

/**
 * @brief Extract a value that is masked inside a bigger bitset.
 * @tparam N Size of bitmask
 * @tparam T Datatype that shall be returned (using static_cast<T>)
 * @param bitset Bitset that shall be evaluated
 * @param start Start position for the first bit
 * @param end End position for the last bit
 * @return Value to be returned
 * @example getBitValue(0xFF, 4,7) will return 15
 */
template<std::size_t N, typename T>
constexpr T
getBitValue(const std::bitset<N> bitset, unsigned int start, unsigned int end) {
    std::bitset<N> mask(((1ULL << (end - start + 1)) - 1) << start);
    auto           result  = bitset & mask;
    auto           shifted = (result >> start) | (result << (N - start));
    return static_cast<T>(shifted.to_ulong());
}

}