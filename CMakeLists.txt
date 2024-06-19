cmake_minimum_required(VERSION 3.26)

option(BUILD_GAME "Build game" ON)

if (BUILD_GAME)
    message(STATUS "Building game")
    set(GAME_MODE TRUE)
    project(Dungeon)
else ()
    project(Editor)
    set(EDITOR_MODE TRUE)
    message(STATUS "Building editor")
endif ()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(DEBUG_MODE TRUE)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(RELEASE_MODE TRUE)
endif()

include(ExternalProject)
include(cmake/CMakeVendor.cmake)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_ROOT_DIR "${CMAKE_SOURCE_DIR}")

set(
        COMMON_FILES
        ${CMAKE_SOURCE_DIR}/source/common/initializer/initializer.cpp
        ${CMAKE_SOURCE_DIR}/source/common/initializer/sdl.cpp
        ${CMAKE_SOURCE_DIR}/source/common/initializer/imgui.cpp

        ${CMAKE_SOURCE_DIR}/source/level/types/assets.cpp
        ${CMAKE_SOURCE_DIR}/source/level/types/tile.cpp
        ${CMAKE_SOURCE_DIR}/source/level/types/door.cpp
        ${CMAKE_SOURCE_DIR}/source/level/types/warp.cpp

        ${CMAKE_SOURCE_DIR}/source/common/handlers.cpp
        ${CMAKE_SOURCE_DIR}/source/common/actionmgr.cpp
        ${CMAKE_SOURCE_DIR}/source/common/scale.cpp
        ${CMAKE_SOURCE_DIR}/source/common/math.cpp
        ${CMAKE_SOURCE_DIR}/source/common/sdl.cpp
        ${CMAKE_SOURCE_DIR}/source/common/perspective.cpp
        ${CMAKE_SOURCE_DIR}/source/common/interrupt.cpp

        ${CMAKE_SOURCE_DIR}/source/graphics/graphics.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/types/simpleTexture.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/generateObjects.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/numbers.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/animatedTexture.cpp


        ${CMAKE_SOURCE_DIR}/source/loaders/loadGraphics.cpp

        ${CMAKE_SOURCE_DIR}/source/level/file.cpp
)

set(
        UTILITY_FILES
        ${CMAKE_SOURCE_DIR}/source/utility/file.cpp
        ${CMAKE_SOURCE_DIR}/source/utility/trigonometry.cpp
        ${CMAKE_SOURCE_DIR}/source/utility/texture.cpp
        ${CMAKE_SOURCE_DIR}/source/utility/math.cpp
)

if (BUILD_GAME)
    add_executable(
            ${PROJECT_NAME}
            ${COMMON_FILES}
            ${UTILITY_FILES}
            ${CMAKE_SOURCE_DIR}/game.cpp

            ${CMAKE_SOURCE_DIR}/source/engine/engine.cpp
            ${CMAKE_SOURCE_DIR}/source/engine/loading.cpp

            ${CMAKE_SOURCE_DIR}/source/engine/level.cpp
            ${CMAKE_SOURCE_DIR}/source/engine/segments.cpp

            ${CMAKE_SOURCE_DIR}/source/player/player.cpp
            ${CMAKE_SOURCE_DIR}/source/player/indicator.cpp

            ${CMAKE_SOURCE_DIR}/source/object/projectile.cpp
            ${CMAKE_SOURCE_DIR}/source/object/particle.cpp
            ${CMAKE_SOURCE_DIR}/source/object/textbox.cpp
            ${CMAKE_SOURCE_DIR}/source/object/door.cpp
            ${CMAKE_SOURCE_DIR}/source/object/warp.cpp

            ${CMAKE_SOURCE_DIR}/source/monster/monster.cpp
            ${CMAKE_SOURCE_DIR}/source/monster/slime.cpp
    )
else ()
    add_executable(
            ${PROJECT_NAME}
            ${COMMON_FILES}
            ${UTILITY_FILES}

            ${CMAKE_SOURCE_DIR}/editor.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/editor.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/visualTile.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/loadLevel.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/ui.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/mouse.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/menu.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/header.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/assets.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/grid.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/tiles.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/textures.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/tile.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/doors.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/warps.cpp
    )
endif ()

message(STATUS "SDL 2 folder: ${SDL2_SOURCE_DIR}")
message(STATUS "SDL_Image 2 folder: ${SDL2_image_SOURCE_DIR}")
message(STATUS "ImGui folder: ${imgui_SOURCE_DIR}")

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${imgui_SOURCE_DIR}         #ImGui folders
        ${CMAKE_CURRENT_BINARY_DIR} #Needed for generated cmake.hpp
)


target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        nlohmann_json::nlohmann_json
        ${LIB_IMGUI}
)

file(
        GLOB RSRC
        ${CMAKE_SOURCE_DIR}/rsrc
)

file(
        COPY ${RSRC}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

configure_file(cmake.hpp.in cmake.hpp @ONLY)

#if(WIN32)
#    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
#endif()
