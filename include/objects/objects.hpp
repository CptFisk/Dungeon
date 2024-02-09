#pragma once
#include <macros.hpp>

namespace Objects {
DEFINE_ENUM_AND_JSON_SERIALIZATION(ObjectAction, IDLE, MOVING, ATTACKING)
}