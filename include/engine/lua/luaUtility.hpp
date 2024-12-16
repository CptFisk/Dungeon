#pragma once
#include <lua.hpp>
#include <utility/trigonometry.hpp>

int utility_getDistance(lua_State* L);
int utility_getAngle(lua_State* L);
int utility_wallObstacle(lua_State* L);
int utility_getVector(lua_State* L); //Calculate a new position based on angle and velocity