#include <engine/lua/luaManager.hpp>
#include <engine/lua/luaMonster.hpp>
#include <lua.hpp>

namespace Lua {

void
LuaManager::registerMonster() {
    luaL_newmetatable(L, "MonsterMeta");
    // Define the methods
    static const luaL_Reg monster_methods[] = {
        { "GetCenter", monster_getCenter },
        { "SetPosition", monster_setPosition },
        { "MovePosition", monster_movePosition },
        { "MoveAngle", monster_moveAngle },
        { "Move", monster_movePosition },
        { "GetVelocity", monster_velocity },
        { "GetState", monster_getState },
        { "SetState", monster_setState },
        { "SetRetain", monster_setRetain },
        { "GetRetain", monster_getRetain },
        { nullptr, nullptr } // Sentinel to indicate the end of the array
    };

    // Register the methods to the metatable
    luaL_setfuncs(L, monster_methods, 0);

    // Set __index field for method lookup
    lua_pushvalue(L, -1);           // Push the metatable itself
    lua_setfield(L, -2, "__index"); // Set __index = metatable
    lua_pop(L, 1);                  // Pop the metatable from the stack
}

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
monster_moveAngle(lua_State* L) {
    auto       monster = checkMonster(L, 1);
    const auto angle   = luaL_checknumber(L, 2);
    if (lua_isnumber(L, 3))
        monster->moveAngle(angle, luaL_checknumber(L, 3));
    monster->moveAngle(angle, std::nullopt);
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

int
monster_setRetain(lua_State* L) {
    auto monster = checkMonster(L, 1);
    if (!lua_isstring(L, 2)) {
        luaL_error(L, "Expected string as key");
    } else {
        const std::string key = luaL_checkstring(L, 2);

        // Integer check
        if (lua_isinteger(L, 3)) {
            monster->setRetain(key, static_cast<int>(lua_tointeger(L, 3)));
        } else if (lua_isnumber(L, 3))
            monster->setRetain(key, static_cast<double>(lua_tonumber(L, 3)));
        else if (lua_isstring(L, 3))
            monster->setRetain(key, std::string(lua_tostring(L, 3)));
        else if (lua_isboolean(L, 3))
            monster->setRetain(key, lua_toboolean(L, 3));
        else
            luaL_error(L, "Unsupported type");
    }
    return 0;
}

int
monster_getRetain(lua_State* L) {
    auto monster = checkMonster(L, 1);
    if (!lua_isstring(L, 2)) {
        luaL_error(L, "Expected key");
        return 0;
    }
    auto key   = std::string(lua_tostring(L, 2));
    auto value = monster->getRetain(key);

    if (!value.has_value()) {
        lua_pushnil(L);
        return 1;
    }
    const auto& retained = value.value();
    // Convert value
    if (value->type() == typeid(int))
        lua_pushinteger(L, std::any_cast<int>(retained));
    else if(value->type() == typeid(float))
        lua_pushnumber(L, std::any_cast<float>(retained));
    else if (value->type() == typeid(double))
        lua_pushnumber(L, std::any_cast<double>(retained));
    else if (value->type() == typeid(std::string))
        lua_pushstring(L, std::any_cast<std::string>(retained).c_str());
    else if (value->type() == typeid(bool))
        lua_pushboolean(L, std::any_cast<bool>(retained));
    else
        lua_pushnil(L);
    return 1;
}
