cmake_minimum_required(VERSION 3.20)
project("Veras adventure")
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

include(ExternalProject)
include(cmake/CMakeVendor.cmake)
include(cmake/CMakeCommon.cmake)
include(cmake/CMakeUtility.cmake)
include(cmake/CMakeFile.cmake)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_ROOT_DIR "${CMAKE_SOURCE_DIR}")


if (BUILD_GAME)
    include(cmake/CMakeHelper.cmake)
    include(cmake/CMakeEngine.cmake)
else ()
    include(cmake/CMakeEditor.cmake)
endif ()

message(STATUS "SDL 2 folder: ${SDL2_SOURCE_DIR}")
message(STATUS "SDL_Image 2 folder: ${SDL2_image_SOURCE_DIR}")
message(STATUS "ImGui folder: ${imgui_SOURCE_DIR}")


file(
        GLOB RSRC
        ${CMAKE_SOURCE_DIR}/rsrc
        ${CMAKE_SOURCE_DIR}/levels
)

file(
        COPY ${RSRC}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

configure_file(cmake.hpp.in cmake.hpp @ONLY)

if(WIN32 AND RELEASE_MODE)
    #set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
