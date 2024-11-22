#include <engine/engine.hpp>
#include <global.hpp>
#include <lua.hpp>

int
lua_MonsterWall(lua_State* L) {
    auto x = static_cast<float>(luaL_checknumber(L, 1));
    int y = static_cast<float>(luaL_checknumber(L, 2));

    extern Engine::Engine engine;
    lua_pushboolean(L, engine.wallCheck(x, y,WALL_OBSTACLE));
    return 1;
}