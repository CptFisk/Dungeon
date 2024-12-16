#include <engine/lua/luaUtility.hpp>
#include <engine/engine.hpp>
int
utility_getDistance(lua_State* L) {
    // Position 1
    const auto x1 = static_cast<float>(luaL_checknumber(L, 1));
    const auto y1 = static_cast<float>(luaL_checknumber(L, 2));
    // Position 2
    const auto x2     = static_cast<float>(luaL_checknumber(L, 3));
    const auto y2     = static_cast<float>(luaL_checknumber(L, 4));
    const auto result = Utility::getDistance({ x1, y1 }, { x2, y2 });
    lua_pushnumber(L, result);
    return 1;
}

int
utility_getAngle(lua_State* L) {
    // Position 1
    const auto x1 = static_cast<float>(luaL_checknumber(L, 1));
    const auto y1 = static_cast<float>(luaL_checknumber(L, 2));
    // Position 2
    const auto x2     = static_cast<float>(luaL_checknumber(L, 3));
    const auto y2     = static_cast<float>(luaL_checknumber(L, 4));
    const auto result = Utility::getAngle({ x1, y1 }, { x2, y2 });
    lua_pushnumber(L, result);
    return 1;
}

int
utility_wallObstacle(lua_State* L) {
    if(!lua_isnumber(L, 1) || !lua_isnumber(L,2)){
        luaL_error(L, "2 floating number is needed");
        lua_pushnil(L);
    }
    const auto x = static_cast<float>(luaL_checknumber(L, 1));
    const auto y = static_cast<float>(luaL_checknumber(L, 2));
    extern Engine::Engine engine;
    lua_pushboolean(L,engine.wallCheck(x, y,WALL_OBSTACLE));
    return 1;
}

int
utility_getVector(lua_State* L){
    if(!lua_isnumber(L, 1) || !lua_isnumber(L,2)){
        luaL_error(L, "2 floating number is needed");
        lua_pushnil(L);
        return 1;
    }

    const auto angle = static_cast<float>(luaL_checknumber(L, 1));
    const auto velocity = static_cast<float>(luaL_checknumber(L, 2));

    const auto pos = Utility::calculateVector(angle, velocity);
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;

}
