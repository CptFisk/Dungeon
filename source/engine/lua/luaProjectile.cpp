#include <engine/lua/luaProjectile.hpp>

int
projectile_spawnEnemy(lua_State* L) {
    /**
     * Parameters as follows:
     * 1 = Texture
     * 2 = Effect (optional)
     * 3 = Start point X
     * 4 = Start point y
     * 5 = Angle
     * 6 = Duration
     * 7 = Velocity
     * 8 = Damage
     */
    if (!lua_isstring(L, 1) || !lua_isstring(L, 2) || !lua_isnumber(L, 3) || !lua_isnumber(L, 4) || !lua_isnumber(L, 5) ||
        !lua_isnumber(L, 6) || !lua_isnumber(L, 7) || !lua_isnumber(L, 8)) {
        const auto p1 = luaL_checkstring(L,2);
        const auto p2 = luaL_checkstring(L,3);
        luaL_error(L, "Parameters incorrect");
        lua_pushnil(L);
    }
    return 1;
}