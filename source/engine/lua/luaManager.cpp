#include <engine/lua/luaManager.hpp>
#include <engine/lua/luaPlayer.hpp>
#include <engine/lua/luaProjectile.hpp>
#include <engine/lua/luaUtility.hpp>
#include <lua.hpp>
#include <object/objects.hpp>
#include <utility/file.hpp>
namespace Lua {

LuaManager::LuaManager() {
    L = luaL_newstate();
    luaopen_base(L);
    lua_setglobal(L, "_G"); // Register the base library in the global namespace
    luaopen_math(L);
    lua_setglobal(L, "math"); // Register the math library in the global namespace

    registerPlayer();
    registerObjectState();
    registerUtility();
    registerMonster();
    registerProjectile();
}

LuaManager::~LuaManager() {
    lua_close(L);
}

lua_State*&
LuaManager::getState() {
    return L;
}

void
LuaManager::createMonsterMetaTable(Monster::BaseMonster*& monster) const {
    auto monsterData = static_cast<Monster::BaseMonster**>(lua_newuserdata(L, sizeof(Monster::BaseMonster*)));
    *monsterData     = monster;
    luaL_setmetatable(L, "MonsterMeta"); // Set the metatable for the userdata
}

bool
LuaManager::executeScript(const std::string& script) {
    // So we dont read the file all the times
    const auto  hash = std::hash<std::string>{}(script);
    std::string content;
    if (mScripts.find(hash) != mScripts.end())
        content = mScripts.at(hash);
    else {
        auto loaded    = Utility::getFileContent(script);
        mScripts[hash] = loaded;
        content        = loaded;
    }
    if (luaL_dostring(L, content.c_str())) {
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
LuaManager::registerObjectState() {
    lua_newtable(L);
    lua_pushinteger(L, Objects::IDLE);
    lua_setfield(L, -2, "IDLE");

    lua_pushinteger(L, Objects::MOVE);
    lua_setfield(L, -2, "MOVE");

    lua_pushinteger(L, Objects::ATTACK);
    lua_setfield(L, -2, "ATTACK");

    lua_pushinteger(L, Objects::DYING);
    lua_setfield(L, -2, "DYING");

    lua_pushinteger(L, Objects::DEAD);
    lua_setfield(L, -2, "DEAD");

    lua_setglobal(L, "ObjectState");
}

void
LuaManager::registerUtility() {
    lua_register(L, "GetDistance", utility_getDistance);
    lua_register(L, "GetAngle", utility_getAngle);
    lua_register(L, "GetAngleDistance", utility_getAngleDistance);
    lua_register(L, "CheckObstacle", utility_wallObstacle);
    lua_register(L, "GetVector", utility_getVector);
}

void
LuaManager::registerPlayer() {
    lua_register(L, "GetPlayerCenter", player_getCenter);
}

void
LuaManager::registerProjectile() {
    lua_register(L, "ProjectileEnemy", projectile_spawnEnemy);
}

}