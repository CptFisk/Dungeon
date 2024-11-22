#pragma once
#include <engine/engine.hpp>
#include <lua.hpp>
#include <monster/monster.hpp>
#include <utility>

namespace Lua {

Monster::BaseMonster*
checkMonster(lua_State* L, int index) {
    return *static_cast<Monster::BaseMonster**>(luaL_checkudata(L, index, "MonsterMeta"));
}

int
monster_getCenter(lua_State* L) {
    auto monster = checkMonster(L, 1);
    auto center  = monster->getCenter();
    lua_pushnumber(L, center.x);
    lua_pushnumber(L, center.y);
    return 2;
}
}

