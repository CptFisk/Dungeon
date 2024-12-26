cmake_minimum_required(VERSION 2.8.12...3.21)
project("Veras adventure")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ENABLE_EXPORTS ON)

option(BUILD_GAME "Build game" ON)

if (BUILD_GAME)
    message(STATUS "Building game")
    set(GAME_MODE TRUE)
else ()
    set(EDITOR_MODE TRUE)
    message(STATUS "Building editor")
endif ()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(DEBUG_MODE TRUE)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(RELEASE_MODE TRUE)
endif()

set(DEBUG_MODE ${DEBUG_MODE} PARENT_SCOPE)
set(RELEASE_MODE ${RELEASE_MODE} PARENT_SCOPE)

add_subdirectory(lua/)
include(ExternalProject)
include(cmake/CMakeVendor.cmake)
include(cmake/CMakeCommon.cmake)
include(cmake/CMakeUtility.cmake)
include(cmake/CMakeFile.cmake)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_ROOT_DIR "${CMAKE_SOURCE_DIR}")


if (BUILD_GAME)
    include(cmake/CmakeEngineLua.cmake)
    include(cmake/CMakeHelper.cmake)
    include(cmake/CMakeEngine.cmake)
else ()
    include(cmake/CMakeEditor.cmake)
endif ()

message(STATUS "SDL 2 folder: ${SDL2_SOURCE_DIR}")
message(STATUS "SDL_Image 2 folder: ${SDL2_image_SOURCE_DIR}")
message(STATUS "ImGui folder: ${imgui_SOURCE_DIR}")


#Move different files based on build-tye
if(BUILD_GAME)
    file(
            GLOB Graphics
            ${CMAKE_SOURCE_DIR}/rsrc/animals
            ${CMAKE_SOURCE_DIR}/rsrc/effects
            ${CMAKE_SOURCE_DIR}/rsrc/font
            ${CMAKE_SOURCE_DIR}/rsrc/generated
            ${CMAKE_SOURCE_DIR}/rsrc/icons
            ${CMAKE_SOURCE_DIR}/rsrc/items
            ${CMAKE_SOURCE_DIR}/rsrc/monster
            ${CMAKE_SOURCE_DIR}/rsrc/player
            ${CMAKE_SOURCE_DIR}/rsrc/projectiles
            ${CMAKE_SOURCE_DIR}/rsrc/spells
            ${CMAKE_SOURCE_DIR}/rsrc/ui
    )
    file(
            GLOB Mics
            ${CMAKE_SOURCE_DIR}/levels
            ${CMAKE_SOURCE_DIR}/scripts
            ${CMAKE_SOURCE_DIR}/items
            ${CMAKE_SOURCE_DIR}/spells
    )
endif()


file(
        COPY ${Graphics}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/rsrc
)
file(
        COPY ${Mics}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/
)


configure_file(cmake.hpp.in cmake.hpp @ONLY)

if(WIN32 AND RELEASE_MODE)
    #set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
