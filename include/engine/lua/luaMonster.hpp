#pragma once
#include <lua.hpp>
#include <monster/monster.hpp>
#include <utility>
#include <engine/engine.hpp>


/**
     * @brief Returns a pointer to a Monster::BaseMonster*
     * @param L Lua_state handler
     * @param index index parameter
     * @return
 */
Monster::BaseMonster* checkMonster(lua_State* L, int index);

int monster_getCenter(lua_State* L);    // Return monster center position through Monster->getCenter()
int monster_setPosition(lua_State* L);  // Set monster position through Monster->setPosition()
int monster_movePosition(lua_State* L); // Set monster position through Monster->movePosition()
int monster_moveAngle(lua_State* L);    // Moves the monster in a specific angle, can have a optional angle as parameter
int monster_velocity(lua_State* L);     // Return the monster velocity
int monster_setState(lua_State* L);     // Set monster state
int monster_getState(lua_State* L);     // Return the current monster state
int monster_setRetain(lua_State* L);    // Set a retain value that can be fetched with getRetain
int monster_getRetain(lua_State* L);    // Get a retain value that can be set with getRetain





