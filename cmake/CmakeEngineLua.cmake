message(STATUS "Engine Lua")

SET(
        ENGINE_LUA
        ${CMAKE_SOURCE_DIR}/source/engine/lua/luaManager.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/lua/luaMonster.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/lua/luaUtility.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/lua/luaPlayer.cpp
)
