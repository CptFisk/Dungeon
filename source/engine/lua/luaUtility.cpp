#include <engine/engine.hpp>
#include <engine/lua/luaUtility.hpp>
#include <utility/trigonometry.hpp>

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
    const auto       x2     = static_cast<float>(luaL_checknumber(L, 3));
    const auto       y2     = static_cast<float>(luaL_checknumber(L, 4));
    const SDL_FPoint x      = { x1, y1 };
    const SDL_FPoint y      = { x2, y2 };
    const auto       result = Utility::getAngle(x, y);
    lua_pushnumber(L, result);
    return 1;
}

int
utility_getAngleDistance(lua_State* L) {
    if (!lua_isnumber(L, 1) || !lua_isnumber(L, 2) || !lua_isnumber(L, 3) || !lua_isnumber(L, 4)) {
        const auto x1 = luaL_checknumber(L, 1);
        const auto x2 = luaL_checknumber(L, 2);
        const auto x3 = luaL_checknumber(L, 3);
        const auto x4 = luaL_checknumber(L, 4);
        luaL_error(L, "4 floating numbers is needed");
        lua_pushnil(L);
        return 0;
    }
    const auto startX   = FLOAT(luaL_checknumber(L, 1));
    const auto startY   = FLOAT(luaL_checknumber(L, 2));
    const auto distance = FLOAT(luaL_checknumber(L, 4));
    const auto pos      = Utility::offsetAngle(SDL_FPoint{ startX, startY }, luaL_checknumber(L, 3), distance);
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}

int
utility_wallObstacle(lua_State* L) {
    if (!lua_isnumber(L, 1) || !lua_isnumber(L, 2)) {
        luaL_error(L, "2 floating number is needed");
        lua_pushnil(L);
    } else {
        const auto            x = static_cast<float>(luaL_checknumber(L, 1));
        const auto            y = static_cast<float>(luaL_checknumber(L, 2));
        extern Engine::Engine engine;
        lua_pushboolean(L, engine.wallCheck(x, y, WALL_OBSTACLE));
    }
    return 1;
}

int
utility_getVector(lua_State* L) {
    if (!lua_isnumber(L, 1) || !lua_isnumber(L, 2)) {
        luaL_error(L, "2 floating number is needed");
        lua_pushnil(L);
        return 1;
    }

    const auto angle    = static_cast<float>(luaL_checknumber(L, 1));
    const auto velocity = static_cast<float>(luaL_checknumber(L, 2));

    const auto pos = Utility::calculateVector(angle, velocity);
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}
