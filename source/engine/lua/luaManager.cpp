#include <engine/lua/luaManager.hpp>
#include <lua.hpp>
#include <engine/lua/monster.hpp>

namespace Lua {

LuaManager::LuaManager() {
    L = luaL_newstate();
    luaopen_base(L);

    registerMonster();
    // Register functions
    // lua_register(L, "SetDarkness", setDarkness);
}

LuaManager::~LuaManager() {
    lua_close(L);
}

lua_State*&
LuaManager::getState() {
    return L;
}

void
LuaManager::createMonsterMetaTable(Monster::BaseMonster*& monster) {
    auto monsterData = static_cast<Monster::BaseMonster**>(lua_newuserdata(L, sizeof(Monster::BaseMonster*)));
    *monsterData     = monster;
    luaL_setmetatable(L, "MonsterMeta"); // Set the metatable for the userdata
}

bool
LuaManager::executeScript(const std::string& script) {
    if (luaL_dofile(L, script.c_str())) {
        std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
        return false;
    }
    return true;
}

bool
LuaManager::callFunction(const std::string& func) {
    lua_getglobal(L, func.c_str());
    // Check if the function exists and is callable
    if (lua_isfunction(L, -1)) {
        // Call the Lua function with 0 arguments and 0 expected results
        if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
            std::cerr << "Error calling function " << func << ": " << lua_tostring(L, -1) << std::endl;
            lua_pop(L, 1); // Remove error message from stack
            return false;
        }
        return true; // Success
    } else {
        std::cerr << "Function " << func << " not found or not callable!" << std::endl;
        lua_pop(L, 1); // Remove non-function value from stack
        return false;
    }
}

std::string
LuaManager::executeString(const std::string& code) {
    std::string result;
    if (luaL_dostring(L, code.c_str()) != LUA_OK) {
        lua_pop(L, 1);
        return "";
    }

    if (lua_gettop(L) > 0) {
        if (lua_isstring(L, -1))
            result = lua_tostring(L, -1);
        else if (lua_isnumber(L, -1))
            result = std::to_string(lua_tonumber(L, -1));
        else if (lua_isboolean(L, -1))
            result = lua_toboolean(L, -1) ? "true" : "false";
        else
            std::cerr << "Unsupported";
    }
    return result;
}

void
LuaManager::registerMonster() {
    luaL_newmetatable(L, "MonsterMeta");

    lua_pushcfunction(L, Lua::monster_getCenter);
    lua_setfield(L, -2, "GetCenter");

    // Set __index field for method lookup
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    lua_pop(L, 1); // Pop metatable from stack
}
}