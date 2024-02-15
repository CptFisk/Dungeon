cmake_minimum_required(VERSION 3.26)
project(CaveMan)

find_package(OpenGL REQUIRED)
include(ExternalProject)
include(cmake/CMakeVendor.cmake)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_ROOT_DIR "${CMAKE_SOURCE_DIR}")

add_executable(
        CaveMan
        main.cpp

        ${CMAKE_SOURCE_DIR}/source/engine/engine.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/initializer.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/sdl.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/interrupt.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/actionmgr.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/handlers.cpp
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
        ${CMAKE_SOURCE_DIR}/source/objects/projectile.cpp
        ${CMAKE_SOURCE_DIR}/source/objects/particle.cpp

)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        SDL3::SDL3
        SDL3_image::SDL3_image
        nlohmann_json::nlohmann_json
)



target_link_libraries(
        ${PROJECT_NAME}

        SDL3::SDL3
        SDL3_image::SDL3_image
        nlohmann_json::nlohmann_json
)

file(
        GLOB RSRC
        ${CMAKE_SOURCE_DIR}/rsrc
)

file(
        COPY ${RSRC}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
