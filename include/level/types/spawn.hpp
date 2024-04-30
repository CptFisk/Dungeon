#pragma onceonce
#include <cstdint>

namespace Level::File{
/**
 * @brief Different type of spawn types
 */
enum class SpawnType : uint8_t { BLANK = 0, MONSTER = 1 << 0 };

/**
 * @brief Data that each specif spawn need's to contain
 */
struct typeSpawn {
    SpawnType Type;     // What type of spawn
    uint8_t   Count;    // Number of that type
    uint8_t   X;        // X-coordinate
    uint8_t   Y;        // Y-coordinate
    char      Name[31]; // Name of the thing to spawn
    typeSpawn()         // Default constructor
      : Type(SpawnType::BLANK)
      , Count(0)
      , X(0)
      , Y(0)
      , Name{} {}
};
}