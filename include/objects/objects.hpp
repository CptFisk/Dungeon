#pragma once
#include <nlohmann/json.hpp>
namespace Objects {
#define OBJECT_ACTION(DO) \
    DO(IDLE)                  \
    DO(MOVE)            \
    DO(ATTACK)

#define MAKE_OBJECT_ACTION(VAR) VAR,
enum ObjectAction {OBJECT_ACTION(MAKE_OBJECT_ACTION)};
NLOHMANN_JSON_SERIALIZE_ENUM(ObjectAction, {{IDLE, "Idle"}, {MOVE, "MOVE"}, {ATTACK, "ATTACK"}})

}