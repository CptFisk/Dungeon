#pragma once
#include <lua.hpp>
#include <engine/engine.hpp>

int
player_getCenter(lua_State* L){

    extern Engine::Engine engine;
    auto center = engine.getPlayer().getPlayerCenter();

    lua_pushnumber(L, center.x);
    lua_pushnumber(L, center.y);

    return 2;
}
