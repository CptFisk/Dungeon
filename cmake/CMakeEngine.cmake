project(Dungeon)

add_executable(
        ${PROJECT_NAME}
        ${COMMON_FILES}
        ${UTILITY_FILES}
        ${HELPERS}
        ${ENGINE_LUA}
        ${CMAKE_SOURCE_DIR}/game.cpp

        ${CMAKE_SOURCE_DIR}/source/engine/engine.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/loading.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/level.cpp

        ${CMAKE_SOURCE_DIR}/source/engine/utility/monsterFactory.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/utility/npcFactory.cpp
        ${CMAKE_SOURCE_DIR}/source/engine/utility/darkness.cpp

        ${CMAKE_SOURCE_DIR}/source/items/itemFactory.cpp
        ${CMAKE_SOURCE_DIR}/source/items/inventory.cpp
        ${CMAKE_SOURCE_DIR}/source/items/item.cpp
        ${CMAKE_SOURCE_DIR}/source/items/weapon.cpp

        ${CMAKE_SOURCE_DIR}/source/player/player.cpp

        #Base for all user interfaces
        ${CMAKE_SOURCE_DIR}/source/ui/userInterface.cpp
        ${CMAKE_SOURCE_DIR}/source/ui/indicators.cpp
        ${CMAKE_SOURCE_DIR}/source/ui/inventory.cpp
        ${CMAKE_SOURCE_DIR}/source/ui/attributes.cpp

        ${CMAKE_SOURCE_DIR}/source/object/projectile.cpp
        ${CMAKE_SOURCE_DIR}/source/object/particle.cpp
        ${CMAKE_SOURCE_DIR}/source/object/door.cpp
        ${CMAKE_SOURCE_DIR}/source/object/warp.cpp

        ${CMAKE_SOURCE_DIR}/source/monster/monster.cpp
        ${CMAKE_SOURCE_DIR}/source/monster/slime.cpp
        ${CMAKE_SOURCE_DIR}/source/monster/caveCrawler.cpp
        ${CMAKE_SOURCE_DIR}/source/monster/beanMan.cpp

        ${CMAKE_SOURCE_DIR}/source/npc/npc.cpp
        ${CMAKE_SOURCE_DIR}/source/npc/cow.cpp

        ${CMAKE_SOURCE_DIR}/source/ui/textbox.cpp
)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/lua
        ${imgui_SOURCE_DIR}         #ImGui folders
        ${CMAKE_CURRENT_BINARY_DIR} #Needed for generated cmake.hpp

)


target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        lua
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        nlohmann_json::nlohmann_json
        ${LIB_COMMON}
        ${LIB_UTILITY}
        ${LIB_FILE}
        ${LUA_MANAGER}
)