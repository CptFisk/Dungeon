#include <engine/lua/luaManager.hpp>
#include <engine/lua/monster.hpp>
#include <lua.hpp>

namespace Lua {
void
LuaManager::registerMonster() {
    luaL_newmetatable(L, "MonsterMeta");

#pragma region Movements
    // Retrieve center position
    lua_pushcfunction(L, Lua::monster_getCenter);
    lua_setfield(L, -2, "GetCenter");

    // Force a new position
    lua_pushcfunction(L, Lua::monster_setPosition);
    lua_setfield(L, -2, "SetPosition");

    // Move relative
    lua_pushcfunction(L, Lua::monster_movePosition);
    lua_setfield(L, -2, "Move");

    // Get velocity
    lua_pushcfunction(L, Lua::monster_velocity);
    lua_setfield(L, -2, "GetVelocity");
#pragma endregion

    lua_pushcfunction(L, Lua::monster_getState);
    lua_setfield(L, -2, "GetState");

    lua_pushcfunction(L, Lua::monster_setState);
    lua_setfield(L, -2, "SetState");

    // Set __index field for method lookup
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    lua_pop(L, 1); // Pop metatable from stack
}
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

int
monster_setPosition(lua_State* L) {
    auto monster = checkMonster(L, 1);
    auto x       = static_cast<float>(luaL_checknumber(L, 2));
    auto y       = static_cast<float>(luaL_checknumber(L, 3));
    monster->setPosition(x, y);
    return 0;
}

int
monster_movePosition(lua_State* L) {
    auto monster = checkMonster(L, 1);
    auto x       = static_cast<float>(luaL_checknumber(L, 2));
    auto y       = static_cast<float>(luaL_checknumber(L, 3));
    monster->movePosition(x, y);
    return 0;
}

int
monster_velocity(lua_State* L) {
    auto monster = checkMonster(L, 1);
    lua_pushnumber(L, monster->getVelocity());
    return 1;
}

int
monster_setState(lua_State* L) {
    auto monster = checkMonster(L, 1);
    auto state   = static_cast<Objects::State>(luaL_checkinteger(L, 2));
    monster->setState(state);
    return 0;
}

int
monster_getState(lua_State* L) {
    auto state = checkMonster(L, 1)->getState();
    lua_pushnumber(L, static_cast<int>(state));
    return 1;
}

}