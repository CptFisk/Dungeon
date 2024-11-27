#include <engine/lua/luaManager.hpp>
#include <engine/lua/luaPlayer.hpp>


namespace Lua{

void
LuaManager::registerPlayer() {
    lua_register(L, "GetPlayerCenter", player_getCenter);
}

}