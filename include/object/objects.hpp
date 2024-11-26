#pragma once
#include <nlohmann/json.hpp>
namespace Objects {

enum State{
    IDLE = 0,
    MOVE = 1,
    ATTACK = 2,
    DYING = 3,
    DEAD = 4
};

NLOHMANN_JSON_SERIALIZE_ENUM(State, { { IDLE, "Idle" }, { MOVE, "MOVE" }, { ATTACK, "ATTACK" } })

}