#pragma once
#include <engine/engine.hpp>
#include <lua.hpp>
#include <monster/monster.hpp>
#include <utility>

namespace Lua {

/**
 * @brief Returns a pointer to a Monster::BaseMonster*
 * @param L Lua_state handler
 * @param index index parameter
 * @return
 */
Monster::BaseMonster*
checkMonster(lua_State* L, int index);

/**
 * @brief Return monster center position through Monster->getCenter()
 */
int
monster_getCenter(lua_State* L);

int
monster_setPosition(lua_State* L);

int
monster_movePosition(lua_State* L);
/**
 * @brief Moves the monster in a specific angle, can have a optional angle as parameter
 * @param L
 */
int
monster_moveAngle(lua_State* L);

/**
 * @brief Return the monster velocity
 */
int
monster_velocity(lua_State* L);

int
monster_setState(lua_State* L);

int
monster_getState(lua_State* L);

/**
 * @brief Set a retain value that can be fetched with getRetain
 */
int
monster_setRetain(lua_State* L);

/**
 * @brief Get a retain value that can be set with getRetain
 */
int
monster_getRetain(lua_State* L);


}


