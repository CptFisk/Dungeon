#pragma once
#include <nlohmann/json.hpp>
namespace Objects {
#define OBJECT_ACTION(DO) \
    DO(IDLE)              \
    DO(MOVE)              \
    DO(ATTACK)            \
    DO(DYING)             \
    DO(DEAD)

#define MAKE_OBJECT_ACTION(VAR) VAR,
enum State { OBJECT_ACTION(MAKE_OBJECT_ACTION) };
NLOHMANN_JSON_SERIALIZE_ENUM(State, { { IDLE, "Idle" }, { MOVE, "MOVE" }, { ATTACK, "ATTACK" } })

}