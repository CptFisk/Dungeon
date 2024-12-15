#include <engine/lua/luaManager.hpp>
#include <engine/lua/luaUtility.hpp>

namespace Lua{
void
LuaManager::registerUtility() {
    lua_register(L, "GetDistance", utility_getDistance);
    lua_register(L, "GetAngle", utility_getAngle);
}

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
utility_getAngle(lua_State* L){
    // Position 1
    const auto x1 = static_cast<float>(luaL_checknumber(L, 1));
    const auto y1 = static_cast<float>(luaL_checknumber(L, 2));
    // Position 2
    const auto x2     = static_cast<float>(luaL_checknumber(L, 3));
    const auto y2     = static_cast<float>(luaL_checknumber(L, 4));
    const auto result = Utility::getAngle({x1,y1}, {x2,y2});
    lua_pushnumber(L, result);
    return 1;
}

}