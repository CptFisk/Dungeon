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

/**
 * @brief Set a value into a specified position inside a bigger bitset.
 * @tparam N Size of bitmask
 * @tparam T Datatype of the value to be set (using static_cast<T>)
 * @param bitset Bitset where the value shall be inserted
 * @param start Start position for the first bit
 * @param end End position for the last bit
 * @param value Value to be inserted
 * @example setBitValue(bitset, 4, 7, 15) will set bits 4 to 7 in bitset to 15
 * @throws std::invalid_argument if the value does not fit in the specified bit range
 */
template<std::size_t N, typename T>
constexpr void
setBitValue(std::bitset<N>& bitset, unsigned int start, unsigned int end, T value) {
    if (start > end || end >= N)
        throw std::invalid_argument("Invalid start or end position");

    unsigned int bitRange = end - start + 1;
    T            maxValue = (1ULL << bitRange) - 1;

    if (static_cast<unsigned long long>(value) > maxValue)
        throw std::invalid_argument("Value does not fit in the specified bit range");

    std::bitset<N> mask(((1ULL << bitRange) - 1) << start);
    std::bitset<N> valueBits(static_cast<unsigned long long>(value) << start);

    // Clear the bits in the specified range
    bitset &= ~mask;

    // Set the bits to the value
    bitset |= (valueBits & mask);
}

}