cmake_minimum_required(VERSION 3.26)

option(BUILD_GAME "Build game" ON)

if (BUILD_GAME)
    message(STATUS "Building game")
    project(Dungeon)
else ()
    project(Editor)
    message(STATUS "Building editor")
endif ()

include(ExternalProject)
include(cmake/CMakeVendor.cmake)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_ROOT_DIR "${CMAKE_SOURCE_DIR}")

set(
        COMMON_FILES
        ${CMAKE_SOURCE_DIR}/source/common/initializer.cpp
        ${CMAKE_SOURCE_DIR}/source/common/sdl.cpp
        ${CMAKE_SOURCE_DIR}/source/common/imgui.cpp
        ${CMAKE_SOURCE_DIR}/source/common/handlers.cpp
        ${CMAKE_SOURCE_DIR}/source/common/actionmgr.cpp
        ${CMAKE_SOURCE_DIR}/source/common/scale.cpp
)

if (BUILD_GAME)
    add_executable(
            ${PROJECT_NAME}
            ${COMMON_FILES}
            game.cpp

            ${CMAKE_SOURCE_DIR}/source/engine/engine.cpp
            ${CMAKE_SOURCE_DIR}/source/engine/interrupt.cpp

            ${CMAKE_SOURCE_DIR}/source/graphics/graphics.cpp
            ${CMAKE_SOURCE_DIR}/source/graphics/generateObjects.cpp
            ${CMAKE_SOURCE_DIR}/source/graphics/loadImage.cpp
            ${CMAKE_SOURCE_DIR}/source/graphics/animatedTexture.cpp
            ${CMAKE_SOURCE_DIR}/source/world/level.cpp
            ${CMAKE_SOURCE_DIR}/source/loaders/loadGraphics.cpp
            ${CMAKE_SOURCE_DIR}/source/utility/file.cpp
            ${CMAKE_SOURCE_DIR}/source/utility/trigonometry.cpp
            ${CMAKE_SOURCE_DIR}/source/utility/texture.cpp
            ${CMAKE_SOURCE_DIR}/source/player/player.cpp
            ${CMAKE_SOURCE_DIR}/source/player/energy.cpp
            ${CMAKE_SOURCE_DIR}/source/objects/obstacle.cpp
            ${CMAKE_SOURCE_DIR}/source/objects/projectile.cpp
            ${CMAKE_SOURCE_DIR}/source/objects/particle.cpp
    )
else ()
    add_executable(
            ${PROJECT_NAME}
            ${COMMON_FILES}
            ${CMAKE_SOURCE_DIR}/editor.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/editor.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/topmenu.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/projectheader.cpp
            ${CMAKE_SOURCE_DIR}/source/editor/grid.cpp
    )
endif ()

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        nlohmann_json::nlohmann_json
        ${IMGUI_INCLUDE_DIRS}
)


target_link_libraries(
        ${PROJECT_NAME}

        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
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
