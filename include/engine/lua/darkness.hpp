#pragma once
#include <engine/engine.hpp>
#include <lua.hpp>

int
setDarkness(lua_State* L) {
    int                   arg1 = luaL_checkinteger(L, 1);
    extern Engine::Engine engine;

    engine.setDarkness(arg1);
    lua_pushinteger(L, 0);
    return 0;
}