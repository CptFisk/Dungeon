cmake_minimum_required(VERSION 3.15)
project(lua LANGUAGES C)

# Add Lua source files
set(LUA_SOURCES
        ${CMAKE_SOURCE_DIR}/lua/lapi.c
        ${CMAKE_SOURCE_DIR}/lua/lcode.c
        ${CMAKE_SOURCE_DIR}/lua/lctype.c
        ${CMAKE_SOURCE_DIR}/lua/ldebug.c
        ${CMAKE_SOURCE_DIR}/lua/ldo.c
        ${CMAKE_SOURCE_DIR}/lua/ldump.c
        ${CMAKE_SOURCE_DIR}/lua/lfunc.c
        ${CMAKE_SOURCE_DIR}/lua/lgc.c
        ${CMAKE_SOURCE_DIR}/lua/llex.c
        ${CMAKE_SOURCE_DIR}/lua/lmem.c
        ${CMAKE_SOURCE_DIR}/lua/lobject.c
        ${CMAKE_SOURCE_DIR}/lua/lopcodes.c
        ${CMAKE_SOURCE_DIR}/lua/lparser.c
        ${CMAKE_SOURCE_DIR}/lua/lstate.c
        ${CMAKE_SOURCE_DIR}/lua/lstring.c
        ${CMAKE_SOURCE_DIR}/lua/ltable.c
        ${CMAKE_SOURCE_DIR}/lua/ltm.c
        ${CMAKE_SOURCE_DIR}/lua/lundump.c
        ${CMAKE_SOURCE_DIR}/lua/lvm.c
        ${CMAKE_SOURCE_DIR}/lua/lzio.c
        ${CMAKE_SOURCE_DIR}/lua/lauxlib.c
        ${CMAKE_SOURCE_DIR}/lua/lbaselib.c
        ${CMAKE_SOURCE_DIR}/lua/ldblib.c
        ${CMAKE_SOURCE_DIR}/lua/liolib.c
        ${CMAKE_SOURCE_DIR}/lua/lmathlib.c
        ${CMAKE_SOURCE_DIR}/lua/loslib.c
        ${CMAKE_SOURCE_DIR}/lua/lstrlib.c
        ${CMAKE_SOURCE_DIR}/lua/ltablib.c
        ${CMAKE_SOURCE_DIR}/lua/linit.c
)

# Create a static library target for Lua
add_library(lua STATIC ${LUA_SOURCES})

# Add include directory for Lua
target_include_directories(lua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
