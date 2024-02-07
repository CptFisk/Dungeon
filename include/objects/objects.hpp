#pragma once
#include <nlohmann/json.hpp>

namespace Objects{
#define ACTION_ENUM(DO) \
    DO(Idle)             \
    DO(Moving)          \
    DO(Attacking)

#define MAKE_ACTION_TYPE(VAR) VAR,
enum ObjectAction { ACTION_ENUM(MAKE_ACTION_TYPE) };
#define MAKE_ACTION_STRINGS(VAR) #VAR,
const char* const getActions[] = { ACTION_ENUM(MAKE_ACTION_STRINGS) };
NLOHMANN_JSON_SERIALIZE_ENUM(ObjectAction,
                             { { Idle, "Idle" },
                               { Moving, "Moving" },
                               { Attacking, "Attacking" }})
}