project(Dungeon)

add_executable(
        ${PROJECT_NAME}
        ${COMMON_FILES}
        ${UTILITY_FILES}
        ${CMAKE_SOURCE_DIR}/game.cpp

        ${CMAKE_SOURCE_DIR}/source/engine/engine.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/loading.cpp

        ${CMAKE_SOURCE_DIR}/source/engine/level.cpp

        ${CMAKE_SOURCE_DIR}/source/engine/utility/monster.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/utility/segments.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/utility/darkness.cpp

        ${CMAKE_SOURCE_DIR}/source/player/player.cpp
        ${CMAKE_SOURCE_DIR}/source/player/indicator.cpp

        ${CMAKE_SOURCE_DIR}/source/object/projectile.cpp
        ${CMAKE_SOURCE_DIR}/source/object/particle.cpp
        ${CMAKE_SOURCE_DIR}/source/object/door.cpp
        ${CMAKE_SOURCE_DIR}/source/object/warp.cpp

        ${CMAKE_SOURCE_DIR}/source/monster/monster.cpp
        ${CMAKE_SOURCE_DIR}/source/monster/slime.cpp
        ${CMAKE_SOURCE_DIR}/source/monster/caveCrawler.cpp

        ${HELPERS}
)

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
        ${LIB_COMMON}
        ${LIB_UTILITY}
)